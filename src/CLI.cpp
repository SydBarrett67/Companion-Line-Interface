#include <iostream>
#include <map>
#include <sstream>
#include <cstdlib>
#include <filesystem>

#include "headers/CLI.h"
#include "headers/Pet.h"
#include "headers/Vars.h"

CLI::CLI(std::vector<Pet>& pets, const std::map<std::string, int>& cfg) : pets(pets), cfg(cfg)
{
    
}

void CLI::parseCommand(std::string command)
{
    std::string cmd = command.substr(0, command.find(' '));
    if (std::find(acceptedCommands.begin(), acceptedCommands.end(), cmd) != acceptedCommands.end()) {
        this->command = command;
        this->executeCommand();
    } else {
        std::cerr << "Command not recognized: " << cmd << "\n";
    }
}

void CLI::executeCommand()
{
    if (this->command.substr(0, 4) == "-new") {
        this->createNewPet();
    }


    if (this->command.substr(0, 4) == "feed") {
        std::string target = this->command.substr(5, this->command.find(' ', 5) - 5);
        this->feed(target);
    }
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

    float factor = (1.0f + ((std::rand() % 21) - 10) / 100.0f);
    
    // Inseriamo il blocco try per intercettare i crash da config mancante
    try {
        Vars vars(
            static_cast<int>(this->cfg.at(type + ".hungerdecay") * factor),
            static_cast<int>(this->cfg.at(type + ".thirstdecay") * factor),
            static_cast<int>(this->cfg.at(type + ".mooddecay")   * factor),
            static_cast<int>(this->cfg.at(type + ".sickchance")  * factor),
            static_cast<int>(this->cfg.at(type + ".lifespan")    * factor)
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
        } else {
            std::cerr << "[!] Usage: feed <pet_name>\n";
        }
    }
    else {
        std::cerr << "[!] Usage: feed <pet_name>\n";
        return;
    }
}



CLI::~CLI()
{
}