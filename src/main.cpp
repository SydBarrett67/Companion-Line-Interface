#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
#include <filesystem>
#include <windows.h>

#include "Pet.h"
#include "ConfigParser.h"

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
            std::cout << "Game tick\n";
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(state.tick)
        );
    }
}

void inputLoop(State& state)
{
    bool fWasPressed = false;

    while (state.running)
    {
        SHORT fState = GetAsyncKeyState('F');
        bool fIsPressed = (fState & 0x8000) != 0;

        if (fIsPressed && !fWasPressed)
        {
            std::lock_guard<std::mutex> lock(state.mtx);
            std::cout << "FEED!\n";
        }

        fWasPressed = fIsPressed;

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            state.running = false;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );
    }
}

int main(int argc, char* argv[])
{
    if (argc>2) {
        if (argv[1] == "-new" || argv[1] == "-n") {
            
        }
    }
    State state;

    ConfigParser cfgParser("../config.txt");
    const auto& cfg = cfgParser.getConfig();

    for (const auto& [key, value] : cfg)
    {
        std::cout << key << " is: " << value << "\n";
    }

    state.tick = cfg.at("tick_ms");

    std::thread game(gameLoop, std::ref(state));
    std::thread input(inputLoop, std::ref(state));

    game.join();
    input.join();

    return 0;
}