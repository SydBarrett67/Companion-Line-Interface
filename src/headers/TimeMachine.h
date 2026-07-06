class TimeMachine {
private:

public:
    static void process(Pet& pet, std::size_t tick = 1, std::size_t timeElapsed = 1) {
        
        pet.increaseHunger(tick, timeElapsed);
        pet.increaseThirst(tick, timeElapsed);
        pet.decreaseMood(tick, timeElapsed);
        pet.increaseAge(tick, timeElapsed);

        pet.saveToFile("data/pets/", pet.getName() + ".pet");
    }
};