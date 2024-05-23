#include "../Headers/J.h"

J::J(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score) {
    block1.setPosition(x, y);
    block2.setPosition(x + size, y);
    block3.setPosition(x + size * 2, y);
    block4.setPosition(x + size * 2, y + size);
}

void J::rotateClockWise() {
    if (landed) return;
    if (!checkCollision(0, 0)) {
        sf::Vector2f pivot = block2.getPosition();

        sf::Vector2f newPos1(pivot.x - (block1.getPosition().y - pivot.y), pivot.y + (block1.getPosition().x - pivot.x));
        sf::Vector2f newPos3(pivot.x - (block3.getPosition().y - pivot.y), pivot.y + (block3.getPosition().x - pivot.x));
        sf::Vector2f newPos4(pivot.x - (block4.getPosition().y - pivot.y), pivot.y + (block4.getPosition().x - pivot.x));

        if (isWithinBounds(newPos1) && isWithinBounds(newPos3) && isWithinBounds(newPos4) &&
            !positionExists(newPos1, landedPositions) && !positionExists(newPos3, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block1.setPosition(newPos1);
            block3.setPosition(newPos3);
            block4.setPosition(newPos4);
        }
    }
}

void J::rotateCounterClockWise() {
    if (landed) return;
    if (!checkCollision(0, 0)) {
        sf::Vector2f pivot = block2.getPosition();

        sf::Vector2f newPos1(pivot.x + (block1.getPosition().y - pivot.y), pivot.y - (block1.getPosition().x - pivot.x));
        sf::Vector2f newPos3(pivot.x + (block3.getPosition().y - pivot.y), pivot.y - (block3.getPosition().x - pivot.x));
        sf::Vector2f newPos4(pivot.x + (block4.getPosition().y - pivot.y), pivot.y - (block4.getPosition().x - pivot.x));

        if (isWithinBounds(newPos1) && isWithinBounds(newPos3) && isWithinBounds(newPos4) &&
            !positionExists(newPos1, landedPositions) && !positionExists(newPos3, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block1.setPosition(newPos1);
            block3.setPosition(newPos3);
            block4.setPosition(newPos4);
        }
    }
}

//empty implementation from basepiece
void J::rotate() {}
