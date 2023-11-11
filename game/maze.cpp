#include "maze.hpp"
#include <vector>
#include <cstdlib>
#include <ncurses.h>
#include <stack>
#include <algorithm>
#include <random>
#include <tuple>
#include <map>
#include <queue>
#include <set>

Maze::Maze(int width, int height) : width_(width), height_(height), goal(width - 2, height - 2) {
    cell.resize(width_, std::vector<bool>(height_, true));
}

void Maze::generateMaze() {
    for (auto &row : cell) {
        std::fill(row.begin(), row.end(), true);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::stack<std::pair<int, int>> stack;
    
    int x = 1, y = 1;
    cell[x][y] = false;
    stack.push({x, y});

    while (!stack.empty()) {
        std::tie(x, y) = stack.top();
        std::vector<std::pair<int, int>> neighbors;

        for (int dx = -2; dx <= 2; dx += 2) {
            for (int dy = -2; dy <= 2; dy += 2) {
                if (dx == 0 || dy == 0) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 1 && nx < width_ - 1 && ny >= 1 && ny < height_ && cell[nx][ny]) {
                        neighbors.push_back({nx, ny});
                    }
                }
            }
        }

        if (!neighbors.empty()) {
            std::shuffle(neighbors.begin(), neighbors.end(), gen);
            std::pair<int, int> next = neighbors.front();

            cell[(x + next.first) / 2][(y + next.second) / 2] = false;
            cell[next.first][next.second] = false;

            stack.push(next);
        } else {
            stack.pop();
        }
    }
}

void Maze::agent_BFS(Maze &maze) {
    std::pair<int, int> start = {1, 1};  // Starting point
    std::queue<std::pair<int, int>> q;
    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    std::set<std::pair<int, int>> path;
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    q.push(start);
    parent[start] = {-1, -1};

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        q.pop();

        if (maze.isGoal(current.first, current.second)) {
            for (std::pair<int, int> at = current; at != std::make_pair(-1, -1); at = parent[at]) {
                path.insert(at);
            }
            break;
        }

        for (const auto &dir : directions) {
            std::pair<int, int> next = {current.first + dir.first, current.second + dir.second};
            if (maze.isWall(!next.first, next.second) && parent.find(next) == parent.end()) {
                parent[next] = current;
                q.push(next);
            }
        }
    }
    maze.agent_display(path);
}


void Maze::display() {
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            if (cell[x][y]) {
                attron(COLOR_PAIR(3));
                mvaddch(y, x, ACS_CKBOARD);
                mvaddch(y, x+93, ACS_CKBOARD);
                attroff(COLOR_PAIR(3));
            }
        }
    }
}

void Maze::agent_display(const std::set<std::pair<int, int>>& path) {
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            if (path.find({x, y}) != path.end()) {
                attron(COLOR_PAIR(2));
                mvaddch(y, x+93, ' ');
                attroff(COLOR_PAIR(2));
            }
        }
    }
}

bool Maze::isWall(int x, int y) {
    return cell[x][y];
}

bool Maze::isGoal(int x, int y) {
    return std::make_pair(x, y) == goal;
}

void Maze::movePlayer(int& playerX, int& playerY, int next_PlayerX, int next_PlayerY, Maze& maze) {
    if (!maze.isWall(next_PlayerX, next_PlayerY)) {
        mvaddch(playerY, playerX, ' ');
        playerX = next_PlayerX;
        playerY = next_PlayerY;
    }
    if (maze.isGoal(playerX, playerY)) {
        /*
        클리어시 화면에 대한 부분 추가 필요
        */
        mvprintw(playerY, playerX, "game clear");
    }
    attron(COLOR_PAIR(1));
    mvaddch(playerY, playerX, '@');
    attroff(COLOR_PAIR(1));
    refresh();
}

void Maze::keyControl(int &playerX, int &playerY, int &next_PlayerX, int &next_PlayerY, Maze &maze, int ch) {
    maze.display();
    attron(COLOR_PAIR(1));
    mvaddch(playerY, playerX, '@');
    attroff(COLOR_PAIR(1));
    switch (ch) {
        case KEY_UP:
        case 'w':
            maze.display();
            next_PlayerY--;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_DOWN:
        case 's':
            maze.display();
            next_PlayerY++;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_LEFT:
        case 'a':
            maze.display();
            next_PlayerX--;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_RIGHT:
        case 'd':
            maze.display();
            next_PlayerX++;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
    }
}