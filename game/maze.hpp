#include <vector>

#ifndef MAZE_HPP
#define MAZE_HPP

class Maze {
public:
    Maze(int width, int height);
    void generateMaze();
    void display();
    bool isWall(int x, int y);
    void movePlayer(int& playerX, int& playerY, int next_PlayerX, int next_PlayerY, Maze& maze);
private:
    int width_;
    int height_;
    std::vector<std::vector<bool>> cell;
};

#endif