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
    std::size_t hungerMax;
    std::size_t thirstMax;
    std::size_t moodMax;
    std::size_t sickchance;
    std::size_t lifespan;

public:
    Pet(std::string name, std::string type, Vars vars, std::string gender);
    Pet(std::string name, std::string type, Vars decays, Vars details, std::string gender);

    // Getters
    std::string getName() const;
    std::string getType() const;
    std::size_t getLastTimeStamp() const;

    // Setters
    void setName(std::string name);

    /*

        std::size_tERACTIONS

    */
    void feed();
    void water();


    /*

        STATS ACTIONS

    */
    void increaseHunger(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void increaseThirst(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void decreaseMood(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void increaseMood(std::size_t amount);
    void increaseAge(std::size_t tick = 1000, std::size_t timeElapsed = 1000);
    void getSick(std::size_t tick = 1000, std::size_t timeElapsed = 1000);

    void saveToFile(std::string path, std::string filename);

    ~Pet();
};

