#include "../Headers/T.h"

T::T(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score) {
    block1.setPosition(x + size, y);
    block2.setPosition(x, y);
    block3.setPosition(x + 2 * size, y);
    block4.setPosition(x + size, y + size);
}

void T::rotateClockWise() {
    if (landed) return;
    if (!checkCollision(0, 0)) {
        sf::Vector2f pivot = block1.getPosition();

        sf::Vector2f newPos2(pivot.x - (block2.getPosition().y - pivot.y), pivot.y + (block2.getPosition().x - pivot.x));
        sf::Vector2f newPos3(pivot.x - (block3.getPosition().y - pivot.y), pivot.y + (block3.getPosition().x - pivot.x));
        sf::Vector2f newPos4(pivot.x - (block4.getPosition().y - pivot.y), pivot.y + (block4.getPosition().x - pivot.x));

        if (isWithinBounds(newPos2) && isWithinBounds(newPos3) && isWithinBounds(newPos4) &&
            !positionExists(newPos2, landedPositions) && !positionExists(newPos3, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block2.setPosition(newPos2);
            block3.setPosition(newPos3);
            block4.setPosition(newPos4);
        }
    }
}

void T::rotateCounterClockWise() {
    if (landed) return;
    if (!checkCollision(0, 0)) {
        sf::Vector2f pivot = block1.getPosition();

        sf::Vector2f newPos2(pivot.x + (block2.getPosition().y - pivot.y), pivot.y - (block2.getPosition().x - pivot.x));
        sf::Vector2f newPos3(pivot.x + (block3.getPosition().y - pivot.y), pivot.y - (block3.getPosition().x - pivot.x));
        sf::Vector2f newPos4(pivot.x + (block4.getPosition().y - pivot.y), pivot.y - (block4.getPosition().x - pivot.x));

        if (isWithinBounds(newPos2) && isWithinBounds(newPos3) && isWithinBounds(newPos4) &&
            !positionExists(newPos2, landedPositions) && !positionExists(newPos3, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block2.setPosition(newPos2);
            block3.setPosition(newPos3);
            block4.setPosition(newPos4);
        }
    }
}

//empty implementation from basepiece
void T::rotate() {}
