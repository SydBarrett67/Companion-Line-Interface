#include <iostream>
#include <chrono>
#include <vector>
#include <windows.h>

// Directions for paddle moving
enum Direction {
    UP,
    DOWN,
    DEFAULT
};

/*

    Structures

*/
struct Paddle {
    int length;
    std::pair<int, int> topXY;
    Direction dir;
    int pts;
};
struct Ball {
    std::pair<int, int> vels;
    std::pair<int, int> xy;
};


Direction calculateBotMove(const Ball& ball, const Paddle& bot) {
    int center = bot.topXY.second + (bot.length / 2);
    // Error hehe
    bool hehe = (rand() % 100) < 5;
    
    if (ball.xy.second < center && !hehe) {
        return UP;
    } 
    else if (ball.xy.second > center && !hehe) {
        return DOWN;
    }

    return DEFAULT;
}

void step(std::vector<std::vector<int>>& grid, Paddle& p1, Paddle& bot, Ball& ball) {
    if (ball.xy.second >= 0 && ball.xy.second < grid.size() && ball.xy.first >= 0 && ball.xy.first < grid[0].size()) {
        grid[ball.xy.second][ball.xy.first] = (ball.xy.first == grid[0].size() / 2) ? 123 : 0;
    }

    for (int y = 0; y < grid.size(); y++) {
        grid[y][p1.topXY.first] = (p1.topXY.first == grid[0].size() / 2) ? 123 : 0;
        grid[y][bot.topXY.first] = (bot.topXY.first == grid[0].size() / 2) ? 123 : 0;
    }
    std::vector<Paddle*> players = { &p1, &bot };

    for (auto* player : players) {
        switch (player->dir) {
        case UP:
            if (player->topXY.second > 0) {
                player->topXY.second--;
            }
            break;
        
        case DOWN:
            if (player->topXY.second + player->length < grid.at(0).size()) {
                player->topXY.second++;
            }
            break;        

        default:
            break;
        }
        
        player->dir = DEFAULT; 
    }
    for (int i = 0; i < p1.length; i++) {
        grid[p1.topXY.second + i][p1.topXY.first] = 1;
    }
    for (int i = 0; i < bot.length; i++) {
        grid[bot.topXY.second + i][bot.topXY.first] = 1;
    }

    // Move ball
    ball.xy.first += ball.vels.first;
    ball.xy.second += ball.vels.second;

    // Bounces
    // Wall
    if (ball.xy.second <= 0 || ball.xy.second >= grid.at(0).size() - 1) {
        ball.vels.second = -ball.vels.second;
        
        if (ball.xy.second <= 0) ball.xy.second = 0;
        if (ball.xy.second >= grid.at(0).size() - 1) ball.xy.second = grid.at(0).size() - 1;
    }
    // Paddles
    if (ball.xy.first == p1.topXY.first) {
        if (ball.xy.second >= p1.topXY.second && ball.xy.second < p1.topXY.second + p1.length) {
            ball.vels.first = -ball.vels.first;
            ball.xy.first = p1.topXY.first + 1;
        }
    }
    else if (ball.xy.first == bot.topXY.first) {
        if (ball.xy.second >= bot.topXY.second && ball.xy.second < bot.topXY.second + bot.length) {
            ball.vels.first = -ball.vels.first;
            ball.xy.first = bot.topXY.first - 1;
        }
    }

    // Points
    if (ball.xy.first < 0) {
        bot.pts++;
        // Reset
        ball.xy = { grid.at(0).size() / 2, grid.at(0).size() / 2 };
        ball.vels.first = 1;
        ball.vels.second = (rand() % 2 == 0) ? 1 : -1;
    } 
    else if (ball.xy.first >= grid.at(0).size()) {
        p1.pts++;
        // reset
        ball.xy = { grid.at(0).size() / 2, grid.at(0).size() / 2 };
        ball.vels.first = -1;
        ball.vels.second = (rand() % 2 == 0) ? 1 : -1;
    }

    if (ball.xy.second >= 0 && ball.xy.second < grid.at(0).size() && ball.xy.first >= 0 && ball.xy.first < grid.at(0).size()) {
        grid[ball.xy.second][ball.xy.first] = 2;
    }
}

void draw(std::vector<std::vector<int>>& grid) {
    for (auto row : grid) {
        for (auto cell : row) {
            switch(cell) {
                case 0:
                    std::cout << "  ";
                    break;

                case 1:
                    std::cout << "# ";
                    break;
                
                case 2:
                    std::cout << "* ";
                    break;

                default:
                    std::cout << "| ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    system("CLS");

    // Player name
    std::string playerName;
    if (argc > 1) playerName = argv[1];
    else playerName = "Player1"; 

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);

    // Game state variables
    bool running = true;
    size_t gameTick = 80;
    auto lastMove = std::chrono::steady_clock::now();

    // Game grid
    const int N = 21;
    std::vector<std::vector<int>> grid(N, std::vector<int>(N, 0));
    for (auto &row : grid) {
        for (int i=0;i<N;i++) {
            if (i == N/2) row.at(i) = 123;
            else row.at(i) = 0;
        }
    }

    // Init player and bot
    Paddle Player = {
        3,
        { 1, N / 2 - 1 },
        DEFAULT,
        0
    };
    Paddle Bot = {
        3,
        { N - 2, N / 2 - 1 },
        DEFAULT,
        0
    };

    srand(time(NULL));
    Ball ball = {
        { (rand() % 2 == 0) ? 1 : -1, (rand() % 2 == 0) ? 1 : -1 },
        { N/2, N/2 }
    };

    // Main loop
    while (running) {
        if      (GetAsyncKeyState(VK_UP)   & 0x8000)   Player.dir  = UP;
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)   Player.dir  = DOWN;
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) running = false;

        auto now = std::chrono::steady_clock::now();

        if (now - lastMove >= std::chrono::milliseconds(gameTick)) {
            Bot.dir = calculateBotMove(ball, Bot);

            step(grid, Player, Bot, ball);

            COORD coord = {0, 0};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            draw(grid);
    
            lastMove = now;

            std::cout << "\n" << playerName << ": " << Player.pts << " | Bot: " << Bot.pts << "    \n";
        }
    }

    return Player.pts;
}