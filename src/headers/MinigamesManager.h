class MinigamesManager
{
private:
    enum GAMES {
        SNAKE,

        // Default fallback
        UNKNOWN
    };

    static GAMES stringToEnum(const std::string& gameName) {
        if (gameName == "snake")  return SNAKE;
        
        return UNKNOWN;
    }
public:

    static void loadMinigames(std::string minigamesDirectory) {
        
    }

    static void startMinigame(std::string gameName) {
        GAMES game = stringToEnum(gameName);
        switch (game) {
            case SNAKE:
                break;
            
            default:
                break;
        }
    }
    
};