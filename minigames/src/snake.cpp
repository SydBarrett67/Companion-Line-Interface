#include <iostream>
#include <chrono>
#include <thread>
#include <deque>
#include <utility>
#include <windows.h>

// Global variables
std::size_t gameTick = 750;
const int N = 10;
int grid[N][N];
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Snake structure
struct Snake {
    std::deque<std::pair<int, int>> cells;
};
// Init player
Snake player = {
    { {N/2, N/2}, {N/2 + 1, N/2}, {N/2 + 2, N/2} }
};

// Apple structure
struct Apple {
    std::pair<int, int> xy;
};


bool check() {


    return true;
}

void step(Direction dir, bool addCell) {
    std::pair<int,int> newHeadPos = player.cells.front();

    switch(dir)
    {
        case UP:    newHeadPos.second--; break;
        case DOWN:  newHeadPos.second++; break;
        case LEFT:  newHeadPos.first--;  break;
        case RIGHT: newHeadPos.first++;  break;
    }

    player.cells.push_front(newHeadPos);

    if (!addCell)
        player.cells.pop_back();
}

Apple getApplePosition() {

    int x,y;
    do {
        x = rand() % N;
        y = rand() % N;
    } while (grid[y][x] > 0);

    grid[y][x] = 3;

    return { {x, y} };
}

void updateGrid(const Apple& apple) {
    // Clear
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            grid[y][x] = 0;

    // Set apple
    grid[apple.xy.second][apple.xy.first] = 3;

    // Set snake
    bool head = true;
    for (const auto& cell : player.cells)
    {
        if (head)
        {
            grid[cell.second][cell.first] = 2;
            head = false;
        }
        else
        {
            grid[cell.second][cell.first] = 1;
        }
    }
}

void draw()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, {0, 0});

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            switch (grid[y][x])
            {
                case 0: std::cout << "  "; break;
                case 1: std::cout << "o "; break;
                case 2: std::cout << "O "; break;
                case 3: std::cout << "@ "; break;
            }
        }
        std::cout << '\n';
    }

    std::cout.flush();
}

int main(int argc, char* argv[]) {
    if (argc > 1) std::string playerName = argv[1];
    else return -1;
    
    system("CLS");

    Direction dir = LEFT;
    
    Apple apple = getApplePosition();

    auto lastMove = std::chrono::steady_clock::now();

    while (check()) {;

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            dir = UP;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            dir = DOWN;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            dir = LEFT;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            dir = RIGHT;
        }

        auto now = std::chrono::steady_clock::now();

        bool gotApple = false;
        if (now - lastMove >= std::chrono::milliseconds(gameTick)) {

            step(dir, gotApple);

            if (gotApple)
                apple = getApplePosition();

            updateGrid(apple);
            draw();

            lastMove = now;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}