#include <string>
#include <fstream>
#include <random>
#include "headers/Vars.h"
#include "headers/Pet.h"

Pet::Pet(std::string name, std::string type, Vars vars, char gender)
{
    // Attribute initialization
    this->name = name;
    this->type = type;
    this->hp = 100;
    this->mood = 100;
    this->age = 0;
    this->gender = gender;
    this->isSick = false;
    this->hunger = 0;
    this->thirst = 0;

    // Specific decays initialization
    this->hungerdecay = vars.getHungerDecay();
    this->thirstdecay = vars.getThirstDecay();
    this->mooddecay = vars.getMoodDecay();
    this->sickchance = vars.getSickChance();
    this->lifespan = vars.getLifespan();
}

std::string Pet::getName() const {
    return this->name;
}
std::string Pet::getType() const {
    return this->type;
}

// Setters
void Pet::setName(std::string name) {
    this->name = name;
}
void Pet::setGender(char gender) {
    this->gender = gender;
}

void Pet::saveToFile(std::string path, std::string filename) {
    std::ofstream file(path + filename);

    if (file.is_open()) {
        file << "name=" << this->name << "\n";
        file << "type=" << this->type << "\n";
        file << "gender=" << this->gender << "\n";
        file << "hp=" << this->hp << "\n";
        file << "mood=" << this->mood << "\n";
        file << "age=" << this->age << "\n";
        file << "isSick=" << this->isSick << "\n";
        file << "hunger=" << this->hunger << "\n";
        file << "thirst=" << this->thirst << "\n";
        
    }
} 

Pet::~Pet()
{
}

