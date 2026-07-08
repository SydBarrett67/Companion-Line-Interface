#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
#include <filesystem>
#include <windows.h>

// Custom header files
#include "headers/Pet.h"
#include "headers/Vars.h"
#include "headers/ConfigParser.h"
#include "headers/CLI.h"
#include "headers/TimeMachine.h"
#include "headers/Logger.h"
#include "headers/Renderer.h"

// Game state structure
struct State
{
    std::atomic<bool> running{true};
    int tick = 1;

    std::vector<Pet> pets;
    std::mutex mtx;
};

void gameLoop(State& state)
{
    int animIndex = 0;
    while (state.running)
    {
        {
            /*
            
                TimeMachine state advancing

            */
            std::lock_guard<std::mutex> lock(state.mtx);
            for (Pet& p : state.pets) {
                const std::size_t timeElapsed = std::time(nullptr) - p.getLastTimeStamp();
                TimeMachine::process(p, state.tick, timeElapsed);
            }

            /*
            
                RENDERER (Graphical Hell)

            */
            Renderer::drawPet(state.pets.at(0), animIndex);

            animIndex = (animIndex + 1) % Renderer::getFrameCountForPet(state.pets.at(0));
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(state.tick)
        );
    }
}

void inputLoop(State& state, CLI &cli)
{
    std::string command;
    while (state.running)
    {
        std::cout << "> " << std::flush;
        if (std::getline(std::cin, command))
        {
            std::lock_guard<std::mutex> lock(state.mtx);
            cli.parseCommand(command);
        }
    }
}

int main(int argc, char* argv[])
{
    system("cls");

    // Get exePath
    std::filesystem::path exePath(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();

    // Renderer init
    Renderer::init_terminal();
    Renderer::loadAnimationsFromFile(std::filesystem::absolute(exeDir / "../../animations/").string());

    std::srand(time(0));

    // Global game state
    State state;
    
    // Parses and loads config file and pets files
    std::filesystem::path configPath = std::filesystem::absolute(exeDir / "../../config.txt");
    std::filesystem::path logPath = std::filesystem::absolute(exeDir / "../../data/log.txt");
    std::filesystem::path statsPath = std::filesystem::absolute(exeDir / "../../data/stats.txt");

    Logger logger(logPath.string(), statsPath.string());
    ConfigParser cfgParser(configPath.string());    

    const auto& cfg = cfgParser.getConfig();
    state.tick = cfg.at("tick_s");
    cfgParser.loadPets((std::filesystem::absolute(exeDir / "../../data/pets")).string(), &state.pets);

    // Built-in CLI for user input
    CLI cli(state.pets, cfg, logger);

    // Thread creation & start
    std::thread game(gameLoop, std::ref(state));
    std::thread input(inputLoop, std::ref(state), std::ref(cli));

    game.join();
    input.join();

    return 0;
}