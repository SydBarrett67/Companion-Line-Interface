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
    this->gender = gender;

    this->hp = 100;
    this->mood = 100;
    this->age = 0;
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

Pet::Pet(std::string name, std::string type, std::size_t age, Vars decays, Vars details, std::string gender) {
    // Attribute initialization
    this->name = name;
    this->type = type;
    this->gender = gender;

    this->hp = details.getHp();
    this->mood = details.getMood();
    this->age = details.getAge();
    this->isSick = false;
    this->hunger = 0;
    this->thirst = 0;

    // Specific decays initialization
    this->hungerdecay = decays.getHungerDecay();
    this->thirstdecay = decays.getThirstDecay();
    this->mooddecay = decays.getMoodDecay();
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
void Pet::feed(std::size_t amount) {
    this->hunger -= amount;
    if (this->hunger < 0) this->hunger = 0;
}
void Pet::water(std::size_t amount) {
    this->thirst -= amount;
    if (this->thirst < 0) this->thirst = 0;
}

/*

    STATS DECREASE

*/
void Pet::increaseHunger(std::size_t tick, std::size_t timeElapsed) {
    this->hunger += this->hungerdecay * timeElapsed / tick;
    if (this->hunger > 100) this->hunger = 100;
}
void Pet::increaseThirst(std::size_t tick, std::size_t timeElapsed) {
    this->thirst += this->thirstdecay * timeElapsed / tick;
    if (this->thirst > 100) this->thirst = 100;
}
void Pet::decreaseMood(std::size_t tick, std::size_t timeElapsed) {
    this->mood -= this->mooddecay * timeElapsed / tick;
    if (this->mood < 0) this->mood = 0;
}
void Pet::increaseAge(std::size_t tick, std::size_t timeElapsed) {
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
        file << "hungerdecay" << this->hungerdecay << "\n";
        file << "thirstdecay" << this->thirstdecay << "\n";
        file << "mooddecay" << this->mooddecay << "\n";
        file << "sickchance" << this->sickchance << "\n";
        file << "lifespan" << this->lifespan << "\n";
        file << "timestamp=" << std::time(nullptr) << "\n";
        file.close();
    }
}


Pet::~Pet()
{
}

