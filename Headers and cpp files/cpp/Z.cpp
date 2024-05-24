#include "../Headers/Z.h"

Z::Z(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score), isVertical(true) {
    block1.setPosition(x, y);
    block2.setPosition(x - size, y);
    block3.setPosition(x, y + size);
    block4.setPosition(x + size, y + size);
}

void Z::rotate() {
    if (landed) return;
    if (!checkCollision(0, 0)) {

        sf::Vector2f pivot = block1.getPosition();
        int size = block1.getSize().x;

        sf::Vector2f newPos2, newPos3, newPos4;
        if (!isVertical) {
            newPos2 = sf::Vector2f(pivot.x - size, pivot.y);
            newPos3 = sf::Vector2f(pivot.x, pivot.y + size);
            newPos4 = sf::Vector2f(pivot.x + size, pivot.y + size);
        } else {
            newPos2 = sf::Vector2f(pivot.x + size, pivot.y);
            newPos3 = sf::Vector2f(pivot.x + size, pivot.y - size);
            newPos4 = sf::Vector2f(pivot.x, pivot.y + size);
        }
        if (isWithinBounds(newPos2) && isWithinBounds(newPos3) && isWithinBounds(newPos4) &&
            !positionExists(newPos2, landedPositions) && !positionExists(newPos3, landedPositions) && !positionExists(newPos4, landedPositions)) {
            block2.setPosition(newPos2);
            block3.setPosition(newPos3);
            block4.setPosition(newPos4);

            isVertical = !isVertical;
        }
    }
}