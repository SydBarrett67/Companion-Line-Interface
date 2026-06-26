#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
#include <windows.h>
#include "Pet.h"
#include "ConfigParser.h"

// GLOBAL STATE
struct State {
    std::atomic<bool> running(true);
    int TICK = 500;

    std::vector<Pet> pets;
    std::mutex mtx;
};


void gameLoop()
{
    while (running)
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Game tick\n";

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TICK));
    }
}

void inputLoop()
{
    bool fWasPressed = false;

    while (running)
    {
        SHORT fState = GetAsyncKeyState('F');

        bool fIsPressed = (fState & 0x8000) != 0;

        if (fIsPressed && !fWasPressed)
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "FEED!\n";
        }

        fWasPressed = fIsPressed;

        // ESC per uscire
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main()
{
    const std::string cfgPath = "config.txt";
    ConfigParser cfgParser(cfgPath);

    const auto& cfg = cfgParser.getConfig();
    for (auto& key : cfg) {
        std::cout << key.first << " is: " << key.second << "\n";
    }
    std::thread game(gameLoop);
    std::thread input(inputLoop);

    game.join();
    input.join();

    return 0;
}