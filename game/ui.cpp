#include <ncurses.h>
#include <string>
#include "ui.hpp"

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
    mvprintw(0, (width - 16) / 2, text);
    if (option == 0){
        mvprintw((height / 2 + 2), (width - 16) / 2, "EXIT");
        mvprintw((height / 2), (width - 16) / 2, "GAME EXPLAIN");
        mvprintw((height / 2 - 2), (width - 16) / 2, "GAME START");
    }
}

void UI::printCursor(int cursor, int width, int height) {
    if (cursor == 0) mvprintw((height / 2 + 2), (width - 16) / 2, "EXIT");
    else if (cursor == 1) mvprintw((height / 2), (width - 16) / 2, "GAME EXPLAIN");
    else if (cursor == 2) mvprintw((height / 2 - 2), (width - 16) / 2, "GAME START");
}

void UI::cleanup() {
    endwin();
}