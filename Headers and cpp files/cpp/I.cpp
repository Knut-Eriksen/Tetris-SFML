#include "../Headers/I.h"

I::I(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score), isVertical(false) {
    block1.setPosition(x - size, y);
    block2.setPosition(x - 2 * size, y);
    block3.setPosition(x, y);
    block4.setPosition(x + size, y);
}

void I::drop() {
    const sf::Time regularDropInterval = sf::milliseconds(700);
    const int dropDistance = 40;

    if (dropClock.getElapsedTime() >= regularDropInterval) {
        if (landed) return;

        if (!checkCollision(0, dropDistance)) {
            block1.move(0, dropDistance);
            block2.move(0, dropDistance);
            block3.move(0, dropDistance);
            block4.move(0, dropDistance);
        } else {
            land();
        }

        dropClock.restart();
    }
}

void I::fastDrop(sf::Keyboard::Key fastDropKey) {
    const sf::Time fastDropInterval = sf::milliseconds(50);
    const int fastDropSpeed = 40;

    if (sf::Keyboard::isKeyPressed(fastDropKey)) {
        fastDropping = true;
        if (dropClock.getElapsedTime() >= fastDropInterval) {
            if (landed) return;

            if (!checkCollision(0, fastDropSpeed)) {
                block1.move(0, fastDropSpeed);
                block2.move(0, fastDropSpeed);
                block3.move(0, fastDropSpeed);
                block4.move(0, fastDropSpeed);
            } else {
                land();
            }
            dropClock.restart();
        }
    } else {
        fastDropping = false;
    }
}

void I::move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) {
    if (landed || movingDown || fastDropping) return;

    const float Movement_Speed = 40;
    if (movementClock.getElapsedTime() > sf::milliseconds(50)) {
        if (sf::Keyboard::isKeyPressed(moveRight) && !checkCollision(Movement_Speed, 0)) {
            block1.move(Movement_Speed, 0);
            block2.move(Movement_Speed, 0);
            block3.move(Movement_Speed, 0);
            block4.move(Movement_Speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(moveLeft) && !checkCollision(-Movement_Speed, 0)) {
            block1.move(-Movement_Speed, 0);
            block2.move(-Movement_Speed, 0);
            block3.move(-Movement_Speed, 0);
            block4.move(-Movement_Speed, 0);
        }
        movementClock.restart();
    }
}

void I::draw(sf::RenderWindow& window) {
    sf::Vector2f blockSize(40, 40);
    for (const auto& pos : landedPositions) {
        sf::RectangleShape block(blockSize);
        block.setPosition(pos);
        block.setFillColor(sf::Color::Blue);
        window.draw(block);
    }

    if (!landed) {
        if (block1.getPosition().y >= 200) window.draw(block1);
        if (block2.getPosition().y >= 200) window.draw(block2);
        if (block3.getPosition().y >= 200) window.draw(block3);
        if (block4.getPosition().y >= 200) window.draw(block4);
    }
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