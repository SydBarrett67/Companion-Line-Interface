#include <string>
#include <fstream>
#include <random>
#include "headers/Vars.h"
#include "headers/Pet.h"

Pet::Pet(std::string name, std::string type, Vars vars, std::string gender)
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

// Getters
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

/*

    INTERACTIONS

*/
void Pet::feed(int amount) {
    this->hunger -= amount;
    if (this->hunger < 0) this->hunger = 0;
}
void Pet::water(int amount) {
    this->thirst -= amount;
    if (this->thirst < 0) this->thirst = 0;
}

/*

    STATS DECREASE

*/
void Pet::decreaseHunger(int tick, int timeElapsed) {
    this->hunger += this->hungerdecay * timeElapsed / tick;
    if (this->hunger > 100) this->hunger = 100;
}
void Pet::decreaseThirst(int tick, int timeElapsed) {
    this->thirst += this->thirstdecay * timeElapsed / tick;
    if (this->thirst > 100) this->thirst = 100;
}
void Pet::decreaseMood(int tick, int timeElapsed) {
    this->mood -= this->mooddecay * timeElapsed / tick;
    if (this->mood < 0) this->mood = 0;
}
void Pet::increaseAge(int tick, int timeElapsed) {
    this->age += timeElapsed / tick;
    if (this->age > this->lifespan) this->age = this->lifespan;
}



// Saving and data handling
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
        file << "timestamp=" << std::time(nullptr) << "\n";
        file.close();
    }
}


Pet::~Pet()
{
}

