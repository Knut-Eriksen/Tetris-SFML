#include "../Headers/S.h"

S::S(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : BasePiece(texture, positions, size, x, y, playerID, score), isVertical(true) {
    block1.setPosition(x, y);
    block2.setPosition(x + size, y);
    block3.setPosition(x, y + size);
    block4.setPosition(x - size, y + size);
}

void S::drop() {
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

void S::fastDrop(sf::Keyboard::Key fastDropKey) {
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

void S::move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) {
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

void S::draw(sf::RenderWindow& window) {
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

void S::rotate() {
    if (landed) return;
    if (!checkCollision(0, 0)) {

        sf::Vector2f pivot = block1.getPosition();
        int size = block1.getSize().x;

        sf::Vector2f newPos2, newPos3, newPos4;
        if (!isVertical) {
            newPos2 = sf::Vector2f(pivot.x + size, pivot.y);
            newPos3 = sf::Vector2f(pivot.x, pivot.y + size);
            newPos4 = sf::Vector2f(pivot.x - size, pivot.y + size);
        } else {
            newPos2 = sf::Vector2f(pivot.x + size, pivot.y);
            newPos3 = sf::Vector2f(pivot.x + size, pivot.y + size);
            newPos4 = sf::Vector2f(pivot.x, pivot.y - size);
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

//empty implementation from basepiece
void S::rotateClockWise() {}

//empty implementation from basepiece
void S::rotateCounterClockWise() {}