#ifndef TETRIS_SFML_MENU_H
#define TETRIS_SFML_MENU_H

#include "SFML/Graphics.hpp"
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
    void updateMenu();  // Update the menu based on the current state

private:
    int selectedIndex;
    sf::Font font;
    sf::Text menu[3]; // 0: Title, 1: Play/Singleplayer, 2: Exit/Multiplayer
    float width, height;
};

#endif //TETRIS_SFML_MENU_H
