#pragma once

#include <string>
#include "headers/Vars.h"

class Pet
{
private:
    // Attributes
    // IDs
    std::string gender;
    std::string type;
    std::string name;

    // Stats
    std::size_t hp;
    std::size_t mood;
    std::size_t hunger;
    std::size_t thirst;
    bool isSick;
    std::size_t age;
    

    // Specific decays
    std::size_t hungerdecay;
    std::size_t thirstdecay;
    std::size_t mooddecay;
    std::size_t sickchance;
    std::size_t lifespan;

public:
    Pet(std::string name, std::string type, Vars vars, std::string gender);
    Pet(std::string name, std::string type, std::size_t age, Vars vars, std::string gender);

    // Getters
    std::string getName() const;
    std::string getType() const;
    std::size_t getLastTimeStamp() const;

    // Setters
    void setName(std::string name);

    /*

        std::size_tERACTIONS

    */
    void feed(std::size_t amount = 100);
    void water(std::size_t amount = 100);


    /*

        STATS DECREASE

    */
    void increaseHunger(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void increaseThirst(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void decreaseMood(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void increaseAge(std::size_t tick = 1000, std::size_t timeElapsed = 1000);

    void saveToFile(std::string path, std::string filename);

    ~Pet();
};

