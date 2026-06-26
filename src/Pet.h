#include <string>

class Pet
{
private:
    int hp;
    int mood;
    int hunger;
    int thirst;
    bool isSick;
    int age;
    std::string type;
    std::string name;

public:
    Pet(std::string name, std::string type);
    ~Pet();
};

