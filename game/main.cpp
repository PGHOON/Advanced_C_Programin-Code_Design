#include <ncurses.h>
#include "ui.hpp"
#include "maze.hpp"
#include <stack>
#include <string>

#define ENTER 10


int main() {
    UI ui;
    ui.initialize();

    int width, height;
    getmaxyx(stdscr, height, width);

    Maze maze(width, height);
    maze.generateMaze();

    int playerX = 1, playerY = 1;
    int menu = 0;
    int cursor = 0;
    int ch;
    ui.drawBorder(0, width, height, " Main menu ");

    while ((ch = getch()) != 'q') {
        if (menu == 0){
            clear();
            ui.drawBorder(0, width, height, " Main menu ");

            switch (ch) {
                case ENTER:
                    if (cursor == 0) {menu = 1; curs_set(0); clear();}
                    break;
                case KEY_UP:
                case 'w':
                    cursor++;
                    if (cursor >= 3) cursor = 0;
                    ui.printCursor(cursor, width, height);
                    break;
                case KEY_DOWN:
                case 's':
                    cursor--;
                    if (cursor < 0) cursor = 2;
                    ui.printCursor(cursor, width, height);
                    
                    break;
            }
        }
        if (menu == 1){
            int next_PlayerX = playerX;
            int next_PlayerY = playerY;
            
            maze.keyControl(playerX, playerY, next_PlayerX, next_PlayerY, maze, ch);
            ui.drawBorder(1, width, height, " Main menu ");
        }
    }

    ui.cleanup();
    return 0;
}