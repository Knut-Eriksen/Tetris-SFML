#ifndef TETRIS_SFML_S_H
#define TETRIS_SFML_S_H

#include "BasePiece.h"

class S : public BasePiece {
public:
    S(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);
    void rotateClockWise() override; //empty implementation
    void rotateCounterClockWise() override; //empty implementation
    void rotate() override;

private:
    bool isVertical;
};

#endif //TETRIS_SFML_S_H
