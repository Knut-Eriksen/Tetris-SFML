#ifndef TETRIS_SFML_MENU_H
#define TETRIS_SFML_MENU_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp."
#include "iostream"

class Menu {
public:
    Menu(float width, float height);
    ~Menu() = default;

    bool PlayPressed = false;

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    void updateMenu();
    void resetMenu();

private:
    int selectedIndex;
    sf::Font font;
    sf::Text menu[3];
    float width, height;
};

#endif //TETRIS_SFML_MENU_H
