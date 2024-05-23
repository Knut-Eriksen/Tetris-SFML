#ifndef TETRIS_SFML_J_H
#define TETRIS_SFML_J_H

#include "BasePiece.h"

class J : public BasePiece {
public:
    J(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);
    void rotateClockWise() override;
    void rotateCounterClockWise() override;
    void rotate() override; //empty implementation since the class is derived from basepiece
};

#endif //TETRIS_SFML_J_H
