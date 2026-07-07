#pragma once

#include "Pet.h"
#include "Logger.h"

#include <map>
#include <vector>
#include <string>

class CLI {
private:
    std::vector<Pet>& pets;
    const std::map<std::string, std::size_t> cfg;
    Logger& logger;

    std::vector<std::string> acceptedCommands = {
        // Animal handling commands
        "-new",         // Create new animal
        "-checkout",    // Select another animal from list
        "-delete",      // Delete an animal .pet file
        "-stats",       // Get single or all animals stats

        // Animal interaction commands
        "feed",
        "water",
        "play",
        "heal",
        
        // Game commands
        "--save",       // Forces saving on all animals if needed
        "--load",       // Reloads all animals if needed
        "--help",       // Prints command list and usages

        // CLI Utilities
        "clear",        // Clears the screen
        "exit", "quit"  // Aliases to quit the game  
    };
    std::string command;


public:
    CLI(std::vector<Pet>& pets, const std::map<std::string, std::size_t>& cfg, Logger& logger);

    void parseCommand(std::string command);
    void executeCommand();

    // COMMAND FUNCTIONS
    void createNewPet();

    // Interaction commands
    void feed(std::string target);
    void water(std::string target);


    // "-help"
    void help();
    ~CLI();
};