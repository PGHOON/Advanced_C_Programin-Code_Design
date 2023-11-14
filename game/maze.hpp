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
#include <thread>
#include <mutex>

#ifndef MAZE_HPP
#define MAZE_HPP

using namespace std;

class Maze {
public:
    Maze(int width, int height);
    void generateMaze();
    void display();
    bool isWall(int x, int y);
    bool isGoal(int x, int y);
    void movePlayer(int& playerX, int& playerY, int next_PlayerX, int next_PlayerY, Maze& maze);
    void keyControl(int &playerX, int &playerY, int &next_PlayerX, int &next_PlayerY, Maze &maze, int ch);

    void agent_BFS(Maze &maze);
    void agent_DFS(Maze &maze);
    void agent_display(const set<pair<int, int>>& path);
private:
    int width_;
    int height_;
    vector<vector<bool>> cell;
    pair<int, int> goal;
    mutex mt;
};

#endif