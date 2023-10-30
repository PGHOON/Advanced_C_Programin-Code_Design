#include <ncurses.h>
#include <string>
#include "ui.hpp"
#define ENTER 10

UI::UI() {
    initscr();
}

void UI::initialize() {
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

void UI::drawBorder(int option, int width, int height, const char *text) {
    border(0, 0, 0, 0, 0, 0, 0, 0);
    mvprintw(0, width / 2 - 6, text);
    if (option == 0){
        mvprintw((height / 2 + 2), (width - 16) / 2, "EXIT");
        mvprintw((height / 2), (width - 16) / 2, "GAME EXPLAIN");
        mvprintw((height / 2 - 2), (width - 16) / 2, "GAME START");
    }
}

void UI::printCursor(int cursor, int width, int height) {
    if (cursor == 2) mvprintw((height / 2 + 2), (width - 16) / 2, "EXIT");
    if (cursor == 1) mvprintw((height / 2), (width - 16) / 2, "GAME EXPLAIN");
    if (cursor == 0) mvprintw((height / 2 - 2), (width - 16) / 2, "GAME START");
}

void UI::menuSelect(int &cursor, int &menu, int width, int height, UI &ui, int ch) {
    printCursor(cursor, width, height);
    switch (ch) {
        case ENTER:
            if (cursor == 0) {menu = 1; curs_set(0); clear();}
            else if(cursor == 1) {menu = 2; curs_set(0); clear();}
            else if(cursor == 2) {ui.cleanup(); exit(0);}
            break;
        case KEY_UP:
        case 'w':
            cursor--;
            if (cursor < 0) cursor = 2;
            ui.printCursor(cursor, width, height);
            break;
        case KEY_DOWN:
        case 's':
            cursor++;
            if (cursor >= 3) cursor = 0;
            ui.printCursor(cursor, width, height);           
            break;
    }
}

void UI::cleanup() {
    endwin();
}