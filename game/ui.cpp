#include <ncurses.h>
#include "ui.hpp"

UI::UI() {
    initscr();
}

void UI::initialize() {
    raw();
    keypad(stdscr, TRUE);
    noecho();
}

void UI::drawBorder(int width, int height) {
    border(0, 0, 0, 0, 0, 0, 0, 0);
    mvprintw(0, (width - 16) / 2, " Simple NCurses UI ");
}

void UI::cleanup() {
    endwin();
}