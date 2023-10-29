#include <string>

#ifndef UI_HPP
#define UI_HPP

class UI {
public:
    UI();
    void initialize();
    void drawBorder(int option, int width, int height, const std::string& text);
    void cleanup();
};

#endif