#pragma once

#include <string>

class Vars
{
private:
    std::size_t hungerdecay;
    std::size_t thirstdecay;
    std::size_t mooddecay;
    std::size_t sickchance;
    std::size_t lifespan;

    std::size_t hp;
    std::size_t age;
    std::size_t hunger;
    std::size_t thirst;
    std::size_t mood;

    bool sick;


public:

    std::size_t getHungerDecay() const { return hungerdecay; }
    std::size_t getThirstDecay() const { return thirstdecay; }
    std::size_t getMoodDecay() const { return mooddecay; }
    std::size_t getSickChance() const { return sickchance; }
    std::size_t getLifespan() const { return lifespan; }

    std::size_t getHp() const { return hp; }
    std::size_t getAge() const { return age; }
    std::size_t getHunger() const { return hunger; }
    std::size_t getThirst() const { return thirst; }
    std::size_t getMood() const { return mood; }

    Vars(std::size_t hungerdecay, std::size_t thirstdecay, std::size_t mooddecay, std::size_t sickchance, std::size_t lifespan);
    Vars(std::size_t hp, std::size_t age, bool sick, std::size_t hunger, std::size_t thirst, std::size_t mood);
    ~Vars();
};

