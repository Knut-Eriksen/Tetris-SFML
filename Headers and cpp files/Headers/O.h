#ifndef TETRIS_SFML_O_H
#define TETRIS_SFML_O_H

#include "BasePiece.h"

class O : public BasePiece {
public:
    O(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);

    void drop() override;
    void fastDrop(sf::Keyboard::Key fastDropKey) override;
    void move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) override;
    void draw(sf::RenderWindow& window) override;
    void rotateClockWise() override; //empty implementation
    void rotateCounterClockWise() override; //empty implementation
    void rotate() override; //empty implementation
};

#endif //TETRIS_SFML_O_H
