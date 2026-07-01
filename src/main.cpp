#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
#include <random>
#include <filesystem>
#include <windows.h>

// Custom header files
#include "headers/Pet.h"
#include "headers/Vars.h"
#include "headers/ConfigParser.h"

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
        }

        fWasPressed = fIsPressed;

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            state.running = false;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );
    }
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    State state;

    ConfigParser cfgParser("../config.txt");
    const auto& cfg = cfgParser.getConfig();
    state.tick = cfg.at("tick_ms");
    
    if (argc >= 4) {
        if (std::strcmp(argv[1], "-new") == 0 || std::strcmp(argv[1], "-n") == 0) {
            // Pet specific vars
            std::string species = std::string(argv[3]);
            
            std::uniform_real_distribution<double> dis(0.90, 1.10);

            Vars vars(
                static_cast<int>(cfg.at(species + ".hungerdecay") * dis(gen)),
                static_cast<int>(cfg.at(species + ".thirstdecay") * dis(gen)),
                static_cast<int>(cfg.at(species + ".mooddecay")   * dis(gen)),
                static_cast<int>(cfg.at(species + ".sickchance")  * dis(gen)),
                static_cast<int>(cfg.at(species + ".lifespan")    * dis(gen))
            );

            Pet pet(argv[2], argv[3], vars);
            if (argc >= 5) {
                pet.setGender(argv[4][0]);
                std::cout << "New pet created: " << argv[2] << " (" << argv[3] << ", " << argv[4][0] << ")\n";
            }
            else {
                std::cout << "New pet created: " << argv[2] << " (" << argv[3] << ")\n";
            }

            std::string filename = argv[2] + std::string(".pet");
            pet.saveToFile("../data/pets/", filename);

            state.pets.push_back(pet);
        }
    }

    for (const auto& pet : state.pets) {
        std::cout << "Pet: " << pet.getName() << " (" << pet.getType() << ")\n";
    }

    std::thread game(gameLoop, std::ref(state));
    std::thread input(inputLoop, std::ref(state));

    game.join();
    input.join();

    return 0;
}