#ifndef TETRIS_SFML_L_H
#define TETRIS_SFML_L_H

#include "BasePiece.h"

class L : public BasePiece {
public:
    L(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);
    void rotateClockWise() override;
    void rotateCounterClockWise() override;
};

#endif //TETRIS_SFML_L_H
