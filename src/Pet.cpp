#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "headers/Vars.h"
#include "headers/Pet.h"

Pet::Pet(std::string name, std::string type, Vars vars, std::string gender)
{
    // Attribute initialization
    this->name = name;
    this->type = type;
    this->gender = gender;

    this->hp = 100;
    this->mood = vars.getMoodMax();
    this->age = 0;
    this->isSick = false;
    this->hunger = 0;
    this->thirst = 0;

    // Specific decays initialization
    this->hungerMax = vars.getHungerMax();
    this->thirstMax = vars.getThirstMax();
    this->moodMax = vars.getMoodMax();
    this->sickchance = vars.getSickChance();
    this->lifespan = vars.getLifespan();
}

Pet::Pet(std::string name, std::string type, Vars decays, Vars details, std::string gender) {
    // Attribute initialization
    this->name = name;
    this->type = type;
    this->gender = gender;

    this->hp = details.getHp();
    this->mood = details.getMood();
    this->age = details.getAge();
    this->isSick = false;
    this->hunger = details.getHunger();
    this->thirst = details.getThirst();

    // Specific decays initialization
    this->hungerMax = decays.getHungerMax();
    this->thirstMax = decays.getThirstMax();
    this->moodMax = decays.getMoodMax();
    this->sickchance = decays.getSickChance();
    this->lifespan = decays.getLifespan();
}

// Getters
std::string Pet::getName() const {
    return this->name;
}
std::string Pet::getType() const {
    return this->type;
}
std::size_t Pet::getLastTimeStamp() const {
    std::ifstream file("data/pets/" + this->name + ".pet");
    std::size_t timestamp = 0;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.substr(0, 10) == "timestamp=") {
                timestamp = std::size_t(std::stoul(line.substr(10)));
                break;
            }
        }
        file.close();
    }
    return timestamp;
}

// Setters
void Pet::setName(std::string name) {
    this->name = name;
}

/*

    Interactions

*/
void Pet::feed() {
    this->hunger = 0;
}
void Pet::water() {
    this->thirst = 0;
}

/*

    STATS DECREASE

*/
void Pet::increaseHunger(std::size_t tick, std::size_t timeElapsed) {
    this->hunger += timeElapsed / tick;
    if (this->hunger > this->hungerMax) this->hunger = this->hungerMax;
}
void Pet::increaseThirst(std::size_t tick, std::size_t timeElapsed) {
    this->thirst += timeElapsed / tick;
    if (this->thirst > this->thirstMax) this->thirst = this->thirstMax;
}
void Pet::decreaseMood(std::size_t tick, std::size_t timeElapsed) {
    this->mood -= timeElapsed / tick;
    if (this->mood < 0) this->mood = 0;
}
void Pet::increaseMood(std::size_t amount) {
    this->mood += amount;
    if (this->mood > this->moodMax) this->mood = this->moodMax;
}
void Pet::increaseAge(std::size_t tick, std::size_t timeElapsed) {
    this->age += timeElapsed / tick;
    if (this->age > this->lifespan) this->age = this->lifespan;
}
void Pet::getSick(std::size_t tick, std::size_t timeElapsed) {
    unsigned long long largeRand = ((unsigned long long)rand() << 32) | rand();
    this->isSick = (largeRand % this->sickchance) == 0;
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
        file << "hungermax=" << this->hungerMax << "\n";
        file << "thirstmax=" << this->thirstMax << "\n";
        file << "moodmax=" << this->moodMax << "\n";
        file << "sickchance=" << this->sickchance << "\n";
        file << "lifespan=" << this->lifespan << "\n";
        file << "timestamp=" << std::time(nullptr);
        file.close();
    }
}


Pet::~Pet()
{
}

