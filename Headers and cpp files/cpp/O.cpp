#include "../Headers/O.h"

O::O(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score) {}


//empty implementation from basepiece
void O::rotateClockWise() {}

//empty implementation from basepiece
void O::rotateCounterClockWise() {}

//empty implementation from basepiece
void O::rotate(){}