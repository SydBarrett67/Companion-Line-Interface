#pragma once

#include <string>
#include "headers/Vars.h"

class Pet
{
private:
    // Attributes
    int hp;
    int mood;
    int hunger;
    int thirst;
    bool isSick;
    int age;
    std::string gender;
    std::string type;
    std::string name;

    // Specific decays
    int hungerdecay;
    int thirstdecay;
    int mooddecay;
    int sickchance;
    int lifespan;

public:
    Pet(std::string name, std::string type, Vars vars, std::string gender);

    // Getters
    std::string getName() const;
    std::string getType() const;

    // Setters
    void setName(std::string name);

    /*

        INTERACTIONS

    */
    void feed(int amount = 100);
    void water(int amount = 100);


    /*

        STATS DECREASE

    */
    void decreaseHunger(int tick = 1000, int timeElapsed = 1000);
    void decreaseThirst(int tick = 1000, int timeElapsed = 1000);
    void decreaseMood(int tick = 1000, int timeElapsed = 1000);
    void increaseAge(int tick = 1000, int timeElapsed = 1000);

    void saveToFile(std::string path, std::string filename);

    ~Pet();
};

