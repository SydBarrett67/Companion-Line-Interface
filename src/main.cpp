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
    while (state.running)
    {
        {
            std::lock_guard<std::mutex> lock(state.mtx);
            // Advance the state of each pet based on the tick interval
            for (Pet& p : state.pets) {
                const std::size_t timeElapsed = std::time(nullptr) - p.getLastTimeStamp();
                TimeMachine::process(p, state.tick, timeElapsed);
            }
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
        std::cout << "> ";
        if (std::getline(std::cin, command))
        {
            std::cout << "\n";

            std::lock_guard<std::mutex> lock(state.mtx);
            cli.parseCommand(command);

            std::cout << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    std::srand(time(0));

    // Global game state
    State state;

    // Parses and loads config file and pets files
    std::filesystem::path exePath(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();
    std::filesystem::path configPath = std::filesystem::absolute(exeDir / "../../config.txt");
    ConfigParser cfgParser(configPath.string());    
    const auto& cfg = cfgParser.getConfig();
    state.tick = cfg.at("tick_s");
    cfgParser.loadPets((std::filesystem::absolute(exeDir / "../../data/pets")).string(), &state.pets);

    // Built-in CLI for user input
    CLI cli(state.pets, cfg);

    // Thread creation & start
    system("cls");
    std::thread game(gameLoop, std::ref(state));
    std::thread input(inputLoop, std::ref(state), std::ref(cli));

    game.join();
    input.join();

    return 0;
}