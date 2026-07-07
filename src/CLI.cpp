#include <iostream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <filesystem>

#include "headers/CLI.h"
#include "headers/Pet.h"
#include "headers/Vars.h"
#include "headers/Logger.h"

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
        std::cout << "\033[30;1H\033[K\033[1;31mCommand not recognized: " << cmd << "\033[0m\n";
    }
}

void CLI::executeCommand()
{
    // Pet creation
    if (this->command.substr(0, 4) == "-new") {
        this->createNewPet();
    }

    // Pet interaction
    if (this->command.substr(0, 4) == "feed") {
        std::string target = this->command.substr(5, this->command.find(' ', 5) - 5);
        this->feed(target);
    }
    if (this->command.substr(0, 5) == "water") {
        std::string target = this->command.substr(5, this->command.find(' ', 5) - 5);
        this->water(target);
    }


    // Game commands
    if (this->command.substr(0, 6) == "--help") {
        this->help();
    }

    // CLI utilities
    if (this->command.substr(0, 5) == "clear") {
        for (int i = CLIStartRow; i <= CLIEndRow; ++i) {
            std::cout << "\033[" << i << ";1H\033[K";
        }
    }
    if (this->command.substr(0, 5) == "exit" || this->command.substr(0, 4) == "quit") {
        std::cout << "\033[30;1H\nExiting program...\n\033[?25h";
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
        std::cerr << "[!] Usage: -new <name> <type> <gender>\n";
        return;
    }

    float factor = (1.0f + ((std::rand() % 21) - CLIEndRow) / 100.0f);
    
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
        std::cerr << "[!] Type: '" << type 
                  << "' not configured correctly.\n"
                  << "(Details: " << e.what() << ")\n";
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
            std::cout << target << "  has been fed successfully!";
        } else {
            std::cerr << "[!] Usage: feed <pet_name>\n";
        }
    }
    else {
        std::cerr << "[!] Usage: feed <pet_name>\n";
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
            std::cout << target << "  has been successfully given water!";
        } else {
            std::cerr << "[!] Usage: water <pet_name>\n";
        }
    }
    else {
        std::cerr << "[!] Usage: water <pet_name>\n";
        return;
    }
}

// "-help" command
void CLI::help() {
    std::cout   << "Command list:\n"
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
                << "--help      :   --help\n";    // Prints all commands usages
}

CLI::~CLI()
{
}