#include "../Headers/Menu.h"

Menu::Menu(float width, float height) : width(width), height(height) {
    if (!font.loadFromFile("Textures/Tetris.ttf")) {
        std::cerr << "Failed to load Font!" << std::endl;
        exit(1);
    }

    // Initialize common properties for menu items
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::White);
    menu[0].setString("Tetris");
    menu[0].setCharacterSize(120);
    menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getGlobalBounds().width / 2, height / 4));

    // Initialize other menu options
    updateMenu();

    selectedIndex = 1;
}

void Menu::updateMenu() {
    if (!PlayPressed) {
        menu[1].setString("Play");
        menu[2].setString("Exit");
        menu[1].setFillColor(sf::Color::Green);
    } else {
        menu[1].setString("Singleplayer");
        menu[2].setString("Multiplayer");
    }

    for (int i = 1; i < 3; i++) {
        menu[i].setFont(font);
        //menu[i].setFillColor(i == selectedIndex ? sf::Color::Green : sf::Color::White);
        menu[i].setCharacterSize(50);
        menu[i].setPosition(sf::Vector2f(width / 2 - menu[i].getGlobalBounds().width / 2, height / 2 + (i - 1) * 100));
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(menu[i]);
    }
}

void Menu::moveUp() {
    if (selectedIndex - 1 >= 1) {
        menu[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menu[selectedIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::moveDown() {
    if (selectedIndex + 1 < 3) {
        menu[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menu[selectedIndex].setFillColor(sf::Color::Green);
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}
