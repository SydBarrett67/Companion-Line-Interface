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

struct State
{
    std::atomic<bool> running{true};
    int tick = 500;

    std::vector<Pet> pets;
    std::mutex mtx;
};

void gameLoop(State& state)
{
    while (state.running)
    {
        {
            std::lock_guard<std::mutex> lock(state.mtx);
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(state.tick)
        );
    }
}

void inputLoop(State& state, CLI &cli)
{
    system("cls");
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

    // Parses and loads the config file
    std::filesystem::path exePath(argv[0]);
    std::filesystem::path exeDir = exePath.parent_path();
    std::filesystem::path configPath = std::filesystem::absolute(exeDir / "../../config.txt");

    ConfigParser cfgParser(configPath.string());    
    const auto& cfg = cfgParser.getConfig();
    state.tick = cfg.at("tick_ms");

    // This parses and executes commands from the built-in CLI
    CLI cli(state.pets, cfgParser.getConfig());

    std::thread game(gameLoop, std::ref(state));
    std::thread input(inputLoop, std::ref(state), std::ref(cli));

    game.join();
    input.join();

    return 0;
}