#include <ncurses.h>
#include "ui.hpp"

int main() {
    UI ui;

    ui.initialize();

    int width, height;
    getmaxyx(stdscr, height, width);

    ui.drawBorder(width, height);
    refresh();

    getch();

    ui.cleanup();

    return 0;
}
