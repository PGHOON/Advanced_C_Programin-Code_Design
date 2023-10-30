#include "maze.hpp"
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <stack>
#include <algorithm>
#include <random>

Maze::Maze(int width, int height) : width_(width), height_(height) {
    cell.resize(width_, std::vector<bool>(height_, true));
}

void Maze::generateMaze() {
    std::stack<std::pair<int, int>> stack;
    stack.push({1, 1});

    std::vector<int> directions = {1, 0, -1, 0, 0, 1, 0, -1};

    std::random_device rd;
    std::mt19937 gen(rd());

    while (!stack.empty()) {
        int x, y;
        std::tie(x, y) = stack.top();
        cell[x][y] = false;
        stack.pop();

        std::shuffle(directions.begin(), directions.end(), gen);

        for (int i = 0; i < 4; i++) {
            int nx = x + directions[i * 2];
            int ny = y + directions[i * 2 + 1];
            if (nx >= 1 && nx < width_ - 1 && ny >= 1 && ny < height_ - 1 && cell[nx][ny]) {
                stack.push({nx, ny});
                cell[(x + nx) / 2][(y + ny) / 2] = false;
            }
        }
    }
}

void Maze::display() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (cell[x][y]) {
                mvaddch(y, x, ACS_CKBOARD);
            }
        }
    }
}

void Maze::TEST_display() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (cell[x][y]) {
                mvaddch(y, x+91, ACS_CKBOARD);
            }
        }
    }
}

bool Maze::isWall(int x, int y) {
    return cell[x][y];
}

void Maze::movePlayer(int& playerX, int& playerY, int next_PlayerX, int next_PlayerY, Maze& maze) {
    if (!maze.isWall(next_PlayerX, next_PlayerY)) {
        playerX = next_PlayerX;
        playerY = next_PlayerY;
    }
    mvaddch(playerY, playerX, '@');
    refresh();
}

void Maze::keyControl(int &playerX, int &playerY, int &next_PlayerX, int &next_PlayerY, Maze &maze, int ch) {
    maze.display();
    mvaddch(playerY, playerX, '@');
    switch (ch) {
        case KEY_UP:
        case 'w':
            clear();
            maze.display();
            next_PlayerY--;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_DOWN:
        case 's':
            clear();
            maze.display();
            next_PlayerY++;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_LEFT:
        case 'a':
            clear();
            maze.display();
            next_PlayerX--;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_RIGHT:
        case 'd':
            clear();
            maze.display();
            next_PlayerX++;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
    }
}