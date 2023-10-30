#include <string>

#ifndef UI_HPP
#define UI_HPP

class UI {
public:
    UI();
    void initialize();
    void drawBorder(int option, int width, int height, const char *text);
    void printCursor(int cursor, int width, int height);
    void menuSelect(int &cursor, int &menu, int width, int height, UI &ui, int ch);
    void cleanup();
};

#endif