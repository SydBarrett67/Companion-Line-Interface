#include "Pet.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <map>
#include <string>

#define CLIStartRow 15
#define CLIEndRow 30

class Renderer {
private:
    std::map<std::string, int> anims;

public:
    static void drawPet(Pet& petToDraw) {
        std::cout << "\033[s";

        std::cout << "\033[1;1H";
        std::cout << "=== PET PANEL ===\n";
        std::cout << "[ ASCII ART ]\n";

        std::cout << "\033[u" << std::flush;
    }

    static void init_terminal() {

        #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
        #endif

        // Clear
        std::cout << "\033[2J\033[H\033[?25l";

        // Scroll
        std::cout << "\033[15;r"; 

        // Cursor on CLI start
        std::cout << "\033[30;1H" << std::flush;
    }
};

