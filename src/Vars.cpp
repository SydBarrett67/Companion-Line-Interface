#include <string>
#include "headers/Vars.h"

Vars::Vars(std::size_t hungerdecay, std::size_t thirstdecay, std::size_t mooddecay, std::size_t sickchance, std::size_t lifespan) 
    : hungerdecay(hungerdecay), 
      thirstdecay(thirstdecay), 
      mooddecay(mooddecay), 
      sickchance(sickchance), 
      lifespan(lifespan)
{
    this->hungerdecay = hungerdecay;
    this->thirstdecay = thirstdecay;
    this->mooddecay = mooddecay;
    this->sickchance = sickchance;
    this->lifespan = lifespan;
}

Vars::Vars(std::size_t hp, std::size_t age, bool sick, std::size_t hunger, std::size_t thirst, std::size_t mood) :
    hp(hp),
    age(age),
    sick(sick),
    hunger(hunger),
    thirst(thirst),
    mood(mood)
{
    this->hp = hp;
    this->age = age;
    this->sick = sick;
    this->hunger = hunger;
    this->thirst = thirst;
    this->mood = mood;
}

Vars::~Vars()
{
}