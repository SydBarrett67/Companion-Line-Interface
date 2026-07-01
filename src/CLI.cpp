#pragma once

#include "headers/CLI.h"
#include <iostream>
#include <map>
#include <cstdlib>
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
                std::cerr << "Target pet not found for feed command.\n";
            }
        }
        else {
            std::cerr << "No target specified for feed command.\n";
            return;
        }

    }
}

/*

    COMMAND FUNCTIONS

*/
// Pet creation
void CLI::createNewPet()
{
    std::cout << "Creating new pet...\n";
    std::string name = this->command.substr(5, this->command.find(' ', 5) - 5);
    std::string type = this->command.substr(this->command.find(' ', 5) + 1);
    std::string gender = this->command.substr(this->command.find(' ', this->command.find(' ', 5) + 1) + 1);

    float factor = (1.0f + ((std::rand() % 21) - 10) / 100.0f);
    Vars vars(
        static_cast<int>(this->cfg.at(type + ".hungerdecay") * factor),
        static_cast<int>(this->cfg.at(type + ".thirstdecay") * factor),
        static_cast<int>(this->cfg.at(type + ".mooddecay")   * factor),
        static_cast<int>(this->cfg.at(type + ".sickchance")  * factor),
        static_cast<int>(this->cfg.at(type + ".lifespan")    * factor)
    );

    Pet pet(name, type, vars, gender);
    std::cout << "New pet created: " << name << " (" << type << ", " << gender << ")\n";

    std::string filename = name + std::string(".pet");
    pet.saveToFile("../data/pets/", filename);

    this->pets.push_back(Pet(name, type, vars, gender));
}

// Interaction commands
void CLI::feed()
{
    // Implementation for feeding a pet
}



CLI::~CLI()
{
}