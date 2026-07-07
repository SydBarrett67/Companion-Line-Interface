#include "Pet.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>

class Renderer {
private:
    /* data */
public:
    static void drawPet(Pet& petToDraw) {
        std::string type = petToDraw.getType();
        std::cout << "\033[1;1H";
    
        std::cout << "===============================\n";
        std::cout << "       ( ASCII ART QUI )       \n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";
        std::cout << "===============================\n";


        std::cout << "\033[16;1H" << std::flush;
    }

    static void init_terminal() {

        #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
        #endif

        std::cout << "\033[2J\033[H" << "\033[?25l" << std::flush;

        std::cout << "\033[16;r"; 

        std::cout << "\033[2J\033[16;1H";

        std::cout << "\033[16;1H" << std::flush;
    }
};

