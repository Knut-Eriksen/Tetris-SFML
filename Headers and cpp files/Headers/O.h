#ifndef TETRIS_SFML_O_H
#define TETRIS_SFML_O_H

#include "BasePiece.h"

class O : public BasePiece {
public:
    O(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);
};

#endif //TETRIS_SFML_O_H
