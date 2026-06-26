#include <string>
#include "Pet.h"

Pet::Pet(std::string name, std::string type)
{
    this->name = name;
    this->type = type;
    this->hp = 100;
    this->mood = 10;
    this->age = 0;
    this->isSick = false;
    this->hunger = 0;
    this->thirst = 0;
}

Pet::~Pet()
{
}

