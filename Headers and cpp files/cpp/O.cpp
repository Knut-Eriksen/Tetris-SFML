#include "../Headers/O.h"

O::O(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score) {}


//setPosition for O piece is the default position declared in BasePiece.cpp
//block1.setPosition(x, y);
//block2.setPosition(x + size, y);
//block3.setPosition(x, y + size);
//block4.setPosition(x + size, y + size);
