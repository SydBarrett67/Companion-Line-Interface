#include <iostream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <filesystem>

#include "headers/CLI.h"
#include "headers/Pet.h"
#include "headers/Vars.h"
#include "headers/Logger.h"
#include "headers/MinigamesManager.h"

#define CLIStartRow 15
#define CLIEndRow 30

CLI::CLI(std::vector<Pet>& pets, const std::map<std::string, std::size_t>& cfg, Logger& logger) 
    :   pets(pets), cfg(cfg), logger(logger)
{
    
}

void CLI::parseCommand(std::string command)
{
    std::string cmd = command.substr(0, command.find(' '));
    if (std::find(acceptedCommands.begin(), acceptedCommands.end(), cmd) != acceptedCommands.end()) {
        this->command = command;
        this->executeCommand();
    } else {
        std::cout << "\033[3m\033[30;1H\033[K\033[1;31mCommand not recognized: " << cmd << "\033[0m\n";
    }
}

void CLI::executeCommand()
{
    // Pet creation
    if (this->command.substr(0, 4) == "-new") {
        this->createNewPet();
    }

    // Select pet to show
    if (this->command.substr(0, 9) == "-checkout") {
        std::stringstream ss(this->command);
        std::string cmd, petName;

        ss >> cmd >> petName;

        this->checkout(petName);
    }

    // Pet interaction
    if (this->command.substr(0, 4) == "feed") {
        size_t space_pos = this->command.find(' ', 4); 
        
        if (space_pos != std::string::npos) {
            std::string target = this->command.substr(space_pos + 1); 
            this->feed(target);
        }
    }
    if (this->command.substr(0, 5) == "water") {
        size_t space_pos = this->command.find(' ', 5); 
        
        if (space_pos != std::string::npos) {
            std::string target = this->command.substr(space_pos + 1); 
            this->water(target);
        }
    }
    if (this->command.substr(0, 4) == "play") {
        std::stringstream ss(this->command);
        std::string cmd, gameName, petName;

        ss >> cmd >> gameName >> petName;

        this->play(gameName, petName);
    }        

    // Game commands
    if (this->command.substr(0, 6) == "--help") {
        this->help();
    }

    // CLI utilities
    if (this->command.substr(0, 5) == "clear" || this->command.substr(0,3) == "cls") {
        for (int i = CLIStartRow; i <= CLIEndRow; ++i) {
            std::cout << "\033[" << i << ";1H\033[K";
        }
    }
    if (this->command.substr(0, 5) == "exit" || this->command.substr(0, 4) == "quit") {
        std::cerr << "\033[3m\033[30;1H\nExiting program...\n\033[?25h";
        system("PAUSE");
        system("CLS");
        exit(0);
    }

    this->logger.log(command);
}

/*

    COMMAND FUNCTIONS

*/
// Pet creation
void CLI::createNewPet()
{
    std::stringstream ss(this->command);
    std::string cmd, name, type, gender;
    ss >> cmd >> name >> type >> gender;

    if (name.empty() || type.empty() || gender.empty()) {
        std::cerr << "\033[31m[!] Usage: -new <name> <type> <gender>\n";
        return;
    }

    float factor = (1.0f + ((std::rand() % 21) - 10.0f) / 100.0f);
    
    try {
        Vars vars(
            static_cast<std::size_t>(this->cfg.at(type + ".hungermax") * factor),
            static_cast<std::size_t>(this->cfg.at(type + ".thirstmax") * factor),
            static_cast<std::size_t>(this->cfg.at(type + ".moodmax")   * factor),
            static_cast<std::size_t>(this->cfg.at(type + ".sickchance")  * factor),
            static_cast<std::size_t>(this->cfg.at(type + ".lifespan")    * factor)
        );

        Pet pet(name, type, vars, gender);
        std::cout << "New pet created: " << name << " (" << type << ", " << gender << ")\n";

        std::filesystem::path folderPath = std::filesystem::absolute("data/pets/");
        std::string filename = name + ".pet";

        std::filesystem::create_directories(folderPath);

        std::filesystem::path fullFilePath = folderPath / filename;

        pet.saveToFile(fullFilePath.string(), ""); 

        this->pets.push_back(std::move(pet));

    } 
    catch (const std::out_of_range& e) {
        std::cerr << "\033[31m[!] Type: '" << type 
                  << "' not configured correctly.\n"
                  << "(Details: " << e.what() << ")\n";
    }
}
void CLI::checkout(std::string petName) {
    if (!petName.empty()) {
        Pet *petToCheckout = nullptr;
        for (auto& pet : this->pets) {
            if (pet.getName() == petName) {
                petToCheckout = &pet;
                break;
            }
        }


        if (petToCheckout != nullptr) {
            std::swap(this->pets[0], *petToCheckout);
            std::cout << petName << " now displaying!\n";
        } else {
            std::cout << "\033[31m[!] Pet not found!\n";
        }
    }
}

// Interaction commands
void CLI::feed(std::string target)
{
    if (!target.empty()) {
        Pet *petToFeed = nullptr;
        for (auto& pet : this->pets) {
            if (pet.getName() == target) {
                petToFeed = &pet;
                break;
            }
        }
        if (petToFeed) {
            petToFeed->feed();
            std::cout << target << " has been fed successfully!\n";
        } else {
            std::cerr << "\033[31m[!] Usage: feed <pet_name>\033[0m\n";
        }
    }
    else {
        std::cerr << "\033[31m[!] Usage: feed <pet_name>\033[0m\n";
        return;
    }
}
void CLI::water(std::string target)
{
    if (!target.empty()) {
        Pet *petToWater = nullptr;
        for (auto& pet : this->pets) {
            if (pet.getName() == target) {
                petToWater = &pet;
                break;
            }
        }
        if (petToWater) {
            petToWater->water();
            std::cout << target << " has been successfully given water!\n";
        } else {
            std::cerr << "\033[31m[!] Usage: water <pet_name>\033[0m\n";
        }
    }
    else {
        std::cerr << "\033[31m[!] Usage: water <pet_name>\033[0m\n";
        return;
    }
}

// Play command
void CLI::play(std::string gameName, std::string petName) {

    if (gameName.empty() || petName.empty()) {
            std::cerr << "\033[1;31m[!] Usage: play <minigame-name> <pet_name>\033[0m\n";
    } 
    else {
        Pet* targetPet = nullptr;
        for (auto& pet : this->pets) {
            if (pet.getName() == petName) {
                targetPet = &pet;
                break;
            }
        }

        if (targetPet != nullptr) {
            size_t points = MinigamesManager::startMinigame(gameName, petName);
            targetPet->increaseMood(points * 1000);

            if (points != 0) std::cout << targetPet->getName() << " is now " << points << " times happier!\n";
        } else {
            std::cerr << "\033[1;31m[!] Pet '" << petName << "' not found!\033[0m\n";
        }
    }
}

// "-help" command
void CLI::help() {
    std::cout   << "\033[3mCommand list:\n"
                << "COMMAND     |   USAGE\n"
                << "-new        :   -new <name> <type> <gender>\n"    // Create new animal
                << "-checkout   :   -checkout <name>\n"               // Select another animal from list
                << "-delete     :   -delete <name>\n"                 // Delete an animal .pet file
                << "-stats      :   -stats {name}\n"                  // Get single or all animals stats

    // Animal interaction commands
                << "feed        :   feed <name>\n"                    // Feed pet
                << "water       :   water <name>\n"                   // Give water to pet
                << "play        :   play <minigame-name> <name>\n"    // Play a minigame with pet
                << "heal        :   heal <name>\n"                    // Attempts to heal sick pet
        
    // Game commands
                << "--save      :   --save\n"     // Forces saving on all animals if needed
                << "--load      :   --load\n"     // Reloads all animals if needed
                << "--help      :   --help\033[0m\n";    // Prints all commands usages
}

CLI::~CLI()
{
}