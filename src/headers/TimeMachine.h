

class TimeMachine {
private:

public:
    static void process(Pet& pet, int tick = 1000, int timeElapsed = 1000) {

        pet.decreaseHunger(tick, timeElapsed);
        pet.decreaseThirst(tick, timeElapsed);
        pet.decreaseMood(tick, timeElapsed);
        pet.increaseAge(tick, timeElapsed);

        // Process the pet's state over time
        // This function should handle the decay of attributes like hunger, thirst, mood, etc.
        // For example:
        // pet.decreaseHunger();
        // pet.decreaseThirst();
        // pet.decreaseMood();

    }

};