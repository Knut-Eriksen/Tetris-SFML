#include "../Headers/I.h"

I::I(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score), isVertical(false) {
    block1.setPosition(x - size, y);
    block2.setPosition(x - 2 * size, y);
    block3.setPosition(x, y);
    block4.setPosition(x + size, y);
}



 void I::rotate() {
        if (landed) return;

        if (!checkCollision(0, 0)) {
            sf::Vector2f pivot = block3.getPosition();
            int size = block3.getSize().x;

            sf::Vector2f newPos1, newPos2, newPos4;
            if (!isVertical) {
                newPos1 = sf::Vector2f(pivot.x, pivot.y - size);
                newPos2 = sf::Vector2f(pivot.x, pivot.y - 2 * size);
                newPos4 = sf::Vector2f(pivot.x, pivot.y + size);
            } else {
                newPos1 = sf::Vector2f(pivot.x - size, pivot.y);
                newPos2 = sf::Vector2f(pivot.x - 2 * size, pivot.y);
                newPos4 = sf::Vector2f(pivot.x + size, pivot.y);
            }
            if (isWithinBounds(newPos1) && isWithinBounds(newPos2) && isWithinBounds(newPos4) &&
                !positionExists(newPos1, landedPositions) && !positionExists(newPos2, landedPositions) && !positionExists(newPos4, landedPositions)) {
                block1.setPosition(newPos1);
                block2.setPosition(newPos2);
                block4.setPosition(newPos4);
                isVertical = !isVertical;
            }
        }
    }

//empty implementation from basepiece
void I::rotateClockWise() {}

//empty implementation from basepiece
void I::rotateCounterClockWise() {}