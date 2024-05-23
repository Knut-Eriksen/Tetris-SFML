#include "../Headers/J.h"

J::J(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score) {
    block1.setPosition(x, y);
    block2.setPosition(x + size, y);
    block3.setPosition(x + size * 2, y);
    block4.setPosition(x + size * 2, y + size);
}

void J::drop() {
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

void J::fastDrop(sf::Keyboard::Key fastDropKey) {
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

void J::move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) {
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

void J::draw(sf::RenderWindow& window) {
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
