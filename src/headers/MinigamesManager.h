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
        
        char exePath[MAX_PATH];
        GetModuleFileNameA(NULL, exePath, MAX_PATH);
        std::filesystem::path p(exePath);
        std::filesystem::path exeFolder = p.parent_path();
        std::filesystem::path targetPath = exeFolder / ".." / "minigames" / "Release";
        std::filesystem::path cleanPath = std::filesystem::weakly_canonical(targetPath);

        // Final minigame directory
        std::string targetDir = cleanPath.string();
        GAMES game = stringToEnum(gameName);
        std::string command;
        
        switch (game) {
            case SNAKE:
                command = targetDir + "\\snake.exe " + petName;
                std::cout << "\" S n a k e \"   m i n i g a m e   b o o t e d\n";
                break;
            
            default:
                std::cerr << "\033[3m\033[30;1H\033[K\033[1;31m[!] Unknown minigame: " << gameName << "\033[0m\n";
                return -1;
        }

        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        bool success = CreateProcessA(
            NULL,                   
            &command[0],            // Command
            NULL,                   
            NULL,                   
            FALSE,                  
            CREATE_NEW_CONSOLE,     // Opens in a new console
            NULL,                   
            targetDir.c_str(),
            &si,                    
            &pi                     
        );

        if (!success) {
            std::cerr << "\033[3m\033[30;1H\033[K\033[1;31m[!] Errors occured while loading minigames. Error code: " << GetLastError() << "\033[0m\n";
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