#include <ncurses.h>
#include "ui.hpp"
#include "maze.hpp"
#include <stack>
#include <string>

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
            curs_set(1);
            ui.drawBorder(0, width, height, " Main menu ");
            ui.menuSelect(cursor, menu, width, height, ui, ch);
        }
        if (menu == 1){
            int next_PlayerX = playerX;
            int next_PlayerY = playerY;
            
            maze.keyControl(playerX, playerY, next_PlayerX, next_PlayerY, maze, ch);
            ui.drawBorder(1, width, height, " Maze game ");
        }
        if (menu == 2){
            ui.drawBorder(1, width, height, " How to Play ");
            menu = 0;
        }
    }

    ui.cleanup();
    return 0;
}