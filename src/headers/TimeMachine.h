class TimeMachine {
private:

public:
    static void process(Pet& pet, int tick = 1000, int timeElapsed = 1000) {
        pet.increaseHunger(tick, timeElapsed);
        pet.increaseThirst(tick, timeElapsed);
        pet.decreaseMood(tick, timeElapsed);
        pet.increaseAge(tick, timeElapsed);

        pet.saveToFile("data/pets/", pet.getName() + ".pet");
        std::cout << "Pet processed, file saved" << std::endl;
    }
};