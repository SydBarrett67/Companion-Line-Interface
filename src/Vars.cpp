#include <string>
#include "headers/Vars.h"

Vars::Vars(int hungerdecay, int thirstdecay, int mooddecay, int sickchance, int lifespan)
{
    this->hungerdecay = hungerdecay;
    this->thirstdecay = thirstdecay;
    this->mooddecay = mooddecay;
    this->sickchance = sickchance;
    this->lifespan = lifespan;
}

Vars::~Vars()
{
}