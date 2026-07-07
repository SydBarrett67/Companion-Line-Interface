#include "Pet.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <map>
#include <vector>
#include <string>

#define CLIStartRow 15
#define CLIEndRow 30

class Renderer {
private:
    inline static std::map<std::string, std::vector<std::string>> anims;

public:
    static void drawPet(Pet& petToDraw, int animIndex) {
        std::cout << "\033[s";

        std::cout << "\033[1;1H";
        std::cout << "Displayed pet: " << petToDraw.getName() << "\n";
        std::cout << anims.at("snake")[animIndex];

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

    static void loadAnimationsFromFile(std::string path) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::filesystem::path filePath = entry.path(); 
            if (std::filesystem::is_regular_file(filePath)) {
                std::ifstream file(filePath);
                
                if (file.is_open()) {
                    std::vector<std::string> frames;
                    std::string line;
                    std::string currentFrame = "";
                    
                    // Separator
                    const std::string separator = "SEPARATOR"; 

                    while (std::getline(file, line)) {
                        if (line == separator) {
                            // Frame's end
                            if (!currentFrame.empty()) {
                                frames.push_back(currentFrame);
                                currentFrame = ""; // Reset for next frame
                            }
                        } else {
                            // Add line to current frame
                            currentFrame += line + "\n";
                        }
                    }

                    if (!currentFrame.empty()) {
                        frames.push_back(currentFrame);
                    }

                    std::string petName = filePath.stem().string(); 

                    anims.insert({ petName, frames });
                }
            }
        }
    }
};

