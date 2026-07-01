#pragma once

#include <string>

class Vars
{
private:
    int hungerdecay;
    int thirstdecay;
    int mooddecay;
    int sickchance;
    int lifespan;

public:

    int getHungerDecay() const { return hungerdecay; }
    int getThirstDecay() const { return thirstdecay; }
    int getMoodDecay() const { return mooddecay; }
    int getSickChance() const { return sickchance; }
    int getLifespan() const { return lifespan; }

    Vars(int hungerdecay, int thirstdecay, int mooddecay, int sickchance, int lifespan);
    ~Vars();
};

