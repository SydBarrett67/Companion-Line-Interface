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
    char gender;
    std::string type;
    std::string name;

    // Specific decays
    int hungerdecay;
    int thirstdecay;
    int mooddecay;
    int sickchance;
    int lifespan;

public:
    Pet(std::string name, std::string type, Vars vars, char gender=(std::rand() % 2 == 0 ? 'M' : 'F'));

    // Getters
    std::string getName() const;
    std::string getType() const;

    // Setters
    void setName(std::string name);
    void setGender(char gender);

    void saveToFile(std::string path, std::string filename);

    ~Pet();
};

