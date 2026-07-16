#include <windows.h>

class MinigamesManager
{
private:
    enum GAMES {
        SNAKE,

        // Default fallback
        UNKNOWN
    };

    // Helper conversion function
    static GAMES stringToEnum(const std::string& gameName) {
        if (gameName == "snake")  return SNAKE;
        
        return UNKNOWN;
    }
public:

    // Start new child process
    static int startMinigame(std::string gameName, std::string petName) {

        // Windows API to create the process
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // Parse gameName
        GAMES game = stringToEnum(gameName);
        std::string command;
        switch (game) {
            case SNAKE:
                command = "../minigames/release/snake.exe " + petName;
                break;
            
            default:
                break;
        }


        bool success = CreateProcessA(
            NULL,                   
            &command[0],            // Command
            NULL,                   
            NULL,                   
            FALSE,                  
            CREATE_NEW_CONSOLE,     // Opens in a new console
            NULL,                   
            NULL,                   
            &si,                    
            &pi                     
        );

        if (!success) {
            std::cerr << "[!] Errors occured while starting minigame.";
            return -1; 
        }

        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode = 0;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return static_cast<int>(exitCode);
    }
    
};