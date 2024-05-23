#ifndef TETRIS_SFML_L_H
#define TETRIS_SFML_L_H

#include "BasePiece.h"

class L : public BasePiece {
public:
    L(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);

    void drop() override;
    void fastDrop(sf::Keyboard::Key fastDropKey) override;
    void move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) override;
    void draw(sf::RenderWindow& window) override;
    void rotateClockWise() override;
    void rotateCounterClockWise() override;
    void rotate() override; //empty implementation since the class is derived from basepiece
};

#endif //TETRIS_SFML_L_H
