#include <iostream>
#include <chrono>
#include <thread>
#include <deque>
#include <utility>
#include <windows.h>

const int N = 10;
int grid[N][N];

struct Snake {
    std::deque<std::pair<int, int>> cells;
};

Snake player = {
    { {N/2, N/2}, {N/2 + 1, N/2}, {N/2 + 2, N/2} }
};

bool check() {


    return true;
}

void step() {

}

void draw() {
    system("cls");
    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            char token;
            switch (grid[i][j]) {
                case 0:
                    token = ' ';
                    break;
                case 1:
                    token = 'o';
                    break;
                case 2:
                    token = 'O';
                    break;
                case 3:
                    token = '@';
                    break;
                default:
                    break;
            }
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) std::string playerName = argv[1];
    else return -1;

    for (int i=0;i<N;i++) {
        for (int j=0;j<N;j++) {
            grid[i][j] = 1;
        }
    }

    std::size_t gameTick = 500;

    while (check()) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {

        }

        step();
        draw();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(gameTick)
        );
    }
}