#include "../Headers/L.h"

L::L(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score) {
    block1.setPosition(x - size, y + size);
    block2.setPosition(x - size, y);
    block3.setPosition(x, y);
    block4.setPosition(x + size, y);
}

void L::rotateClockWise() {
    if (landed) return;
    if (!checkCollision(0, 0)) {
        sf::Vector2f pivot = block3.getPosition();

        sf::Vector2f newPos1(pivot.x - (block1.getPosition().y - pivot.y), pivot.y + (block1.getPosition().x - pivot.x));
        sf::Vector2f newPos2(pivot.x - (block2.getPosition().y - pivot.y), pivot.y + (block2.getPosition().x - pivot.x));
        sf::Vector2f newPos4(pivot.x - (block4.getPosition().y - pivot.y), pivot.y + (block4.getPosition().x - pivot.x));

        if (isWithinBounds(newPos1) && isWithinBounds(newPos2) && isWithinBounds(newPos4) &&
            !positionExists(newPos1, landedPositions) && !positionExists(newPos2, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block1.setPosition(newPos1);
            block2.setPosition(newPos2);
            block4.setPosition(newPos4);
        }
    }
}

void L::rotateCounterClockWise() {
    if (landed) return;
    if (!checkCollision(0, 0)) {
        sf::Vector2f pivot = block3.getPosition();

        sf::Vector2f newPos1(pivot.x + (block1.getPosition().y - pivot.y), pivot.y - (block1.getPosition().x - pivot.x));
        sf::Vector2f newPos2(pivot.x + (block2.getPosition().y - pivot.y), pivot.y - (block2.getPosition().x - pivot.x));
        sf::Vector2f newPos4(pivot.x + (block4.getPosition().y - pivot.y), pivot.y - (block4.getPosition().x - pivot.x));

        if (isWithinBounds(newPos1) && isWithinBounds(newPos2) && isWithinBounds(newPos4) &&
            !positionExists(newPos1, landedPositions) && !positionExists(newPos2, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block1.setPosition(newPos1);
            block2.setPosition(newPos2);
            block4.setPosition(newPos4);
        }
    }
}
