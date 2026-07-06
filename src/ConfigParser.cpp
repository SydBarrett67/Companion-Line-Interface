#include <iostream>
#include <filesystem>
#include "headers/Pet.h"
#include "headers/ConfigParser.h"

ConfigParser::ConfigParser(std::string cfgPath)
{
    try {
        std::ifstream file(cfgPath);

        std::string line = "";
        while(std::getline(file, line)) {
            size_t pos = line.find('=');
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            cfg[key] = std::size_t(std::stoull(value));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error opening config file: " << e.what() << "\n";
        std::cerr << "Last key: " << cfg.rbegin()->first << ", Last value: " << cfg.rbegin()->second << "\n";
        return;
    }
    
}

const std::map<std::string, std::size_t> ConfigParser::getConfig() const{
    return this->cfg;
}

void ConfigParser::loadPets(std::string path, std::vector<Pet> *pets)
{
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".pet") {
            std::ifstream file(entry.path());
            // IDs
            std::string name, 
                        type,
                        gender;

            // Stats
            std::size_t hp, age, thirst, hunger, mood,

            // Specific decays
                        hungerMax, thirstMax, moodmax, sickchance, lifespan;
            
            bool sick;
            std::string line;

            while (std::getline(file, line)) {
                size_t pos = line.find('=');
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);

                // IDs
                if (key == "name") name = value;
                else if (key == "type") type = value;
                else if (key == "gender") gender = value;

                // Stats
                else if (key == "hp") hp = std::size_t(std::stoull(value));
                else if (key == "age") age = std::size_t(std::stoull(value));
                else if (key == "mood") mood = std::size_t(std::stoull(value));
                else if (key == "thirst") thirst = std::size_t(std::stoull(value));
                else if (key == "hunger") hunger = std::size_t(std::stoull(value));
                else if (key == "isSick") sick = static_cast<bool>(std::stoi(value));

                // Specific decays
                else if (key == "hungermax") hungerMax = std::size_t(std::stoull(value));
                else if (key == "thirstmax") thirstMax = std::size_t(std::stoull(value));
                else if (key == "moodmax") moodmax = std::size_t(std::stoull(value));
                else if (key == "sickchance") sickchance = std::size_t(std::stoull(value));
                else if (key == "lifespan") lifespan = std::size_t(std::stoull(value));
            }

            pets->push_back(Pet(name, type, Vars(hungerMax, thirstMax, moodmax, sickchance, lifespan), Vars(hp, age, sick, hunger, thirst, mood), gender));
        }
    }
}

ConfigParser::~ConfigParser() {

}