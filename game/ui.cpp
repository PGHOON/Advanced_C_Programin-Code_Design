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

void UI::drawBorder(int option, int width, int height, const std::string& text) {
    if (option == 0){
        mvprintw((height / 2 - 2), (width - 16) / 2, "GAME START");
        mvprintw((height / 2), (width - 16) / 2, "GAME EXPLAIN");
        mvprintw((height / 2 + 2), (width - 16) / 2, "EXIT");
    }
    border(0, 0, 0, 0, 0, 0, 0, 0);
    mvprintw(0, (width - 16) / 2, text.c_str());
}

void UI::cleanup() {
    endwin();
}