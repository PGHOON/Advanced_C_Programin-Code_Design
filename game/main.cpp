#include <ncurses.h>
#include "ui.hpp"
#include "maze.hpp"
#include <stack>

int main() {
    UI ui;
    ui.initialize();
    curs_set(0);

    int width, height;
    getmaxyx(stdscr, height, width);

    Maze maze(width, height);
    maze.generateMaze();

    int playerX = 1, playerY = 1;

    while (true) {
        clear();
        maze.display();
        ui.drawBorder(width, height);
        mvaddch(playerY, playerX, '@');
        refresh();

        int ch = getch();
        if (ch == 'q') {
            break;
        }

        int next_PlayerX = playerX;
        int next_PlayerY = playerY;

        switch (ch) {
            case KEY_UP:
            case 'w':
                next_PlayerY--;
                break;
            case KEY_DOWN:
            case 's':
                next_PlayerY++;
                break;
            case KEY_LEFT:
            case 'a':
                next_PlayerX--;
                break;
            case KEY_RIGHT:
            case 'd':
                next_PlayerX++;
                break;
        }

        if (!maze.isWall(next_PlayerX, next_PlayerY)) {
            playerX = next_PlayerX;
            playerY = next_PlayerY;
        }
    }

    ui.cleanup();
    return 0;
}
