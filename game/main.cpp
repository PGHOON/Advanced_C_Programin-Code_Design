#include <ncurses.h>
#include "ui.hpp"
#include "maze.hpp"
#include <stack>
#include <string>

int main() {
    UI ui;
    ui.initialize();
    curs_set(0);

    int width, height;
    getmaxyx(stdscr, height, width);

    Maze maze(width, height);
    maze.generateMaze();

    int playerX = 1, playerY = 1;
    int menu = 1;
    int ch;

    while ((ch = getch()) != 'q') {
        if (menu == 0){
            clear();
            ui.drawBorder(0, width, height, " Main menu ");

        }
        else if (menu == 1){
            clear();
            maze.display();
            ui.drawBorder(1, width, height, " Main menu ");
            
            int next_PlayerX = playerX;
            int next_PlayerY = playerY;
            

            switch (ch) {
                case KEY_UP:
                case 'w':
                    next_PlayerY--;
                    maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
                    break;
                case KEY_DOWN:
                case 's':
                    next_PlayerY++;
                    maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
                    break;
                case KEY_LEFT:
                case 'a':
                    next_PlayerX--;
                    maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
                    break;
                case KEY_RIGHT:
                case 'd':
                    next_PlayerX++;
                    maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
                    break;
            }
        }
    }

    ui.cleanup();
    return 0;
}
