#pragma once

#include "Pet.h"
#include <map>
#include <vector>
#include <string>

class CLI {
private:
    std::vector<Pet>& pets;
    const std::map<std::string, std::size_t> cfg;
    std::vector<std::string> acceptedCommands = {
        // Animal handling commands
        "-new",
        "-checkout",
        "-delete",
        "-stats",

        // Animal interaction commands
        "feed",
        "water",
        "play",
        "heal",
        
        // Game commands
        "--save",
        "--load",
        "--help",
    };
    std::string command;


public:
    CLI(std::vector<Pet>& pets, const std::map<std::string, std::size_t>& cfg);

    void parseCommand(std::string command);
    void executeCommand();

    // COMMAND FUNCTIONS
    void createNewPet();

    // Interaction commands
    void feed(std::string target);
    void water();

    ~CLI();
};