#include "../Headers/BasePiece.h"
#include <iostream>

BasePiece::BasePiece(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : landedPositions(positions), playerID(playerID), drop_speed(0, 40), score(score), landed(false) {
    block1 = sf::RectangleShape(sf::Vector2f(size, size));
    block2 = sf::RectangleShape(sf::Vector2f(size, size));
    block3 = sf::RectangleShape(sf::Vector2f(size, size));
    block4 = sf::RectangleShape(sf::Vector2f(size, size));


    block1.setTexture(&texture);
    block2.setTexture(&texture);
    block3.setTexture(&texture);
    block4.setTexture(&texture);

    block1.setPosition(x, y);
    block2.setPosition(x + size, y);
    block3.setPosition(x, y + size);
    block4.setPosition(x + size, y + size);
}

void BasePiece::move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) {
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

void BasePiece::fastDrop(sf::Keyboard::Key fastDropKey) {
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


void BasePiece::drop() {
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

void BasePiece::draw(sf::RenderWindow& window) {
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

bool BasePiece::checkCollision(float dx, float dy) {
    int minX, maxX;
    if (playerID == 1) {
        minX = 300; maxX = 660;
    } else {
        minX = 1300; maxX = 1660;
    }

    for (const auto &pos : landedPositions) {
        if ((block1.getPosition().x + dx == pos.x && block1.getPosition().y + dy == pos.y) ||
            (block2.getPosition().x + dx == pos.x && block2.getPosition().y + dy == pos.y) ||
            (block3.getPosition().x + dx == pos.x && block3.getPosition().y + dy == pos.y) ||
            (block4.getPosition().x + dx == pos.x && block4.getPosition().y + dy == pos.y)) {
            return true;
        }
    }

    if ((dx > 0 && (block1.getPosition().x + dx > maxX || block2.getPosition().x + dx > maxX ||
                    block3.getPosition().x + dx > maxX || block4.getPosition().x + dx > maxX)) ||
        (dx < 0 && (block1.getPosition().x + dx < minX || block2.getPosition().x + dx < minX ||
                    block3.getPosition().x + dx < minX || block4.getPosition().x + dx < minX))) {
        return true;
    }

    if (dy > 0 && (block1.getPosition().y + dy + block1.getSize().y > 1000 ||
                   block2.getPosition().y + dy + block2.getSize().y > 1000 ||
                   block3.getPosition().y + dy + block3.getSize().y > 1000 ||
                   block4.getPosition().y + dy + block4.getSize().y > 1000)) {
        return true;
    }

    return false;
}

void BasePiece::addPosition(const sf::Vector2f &position, std::vector<sf::Vector2f> &positions) {
    if (!positionExists(position, positions)) {
        positions.push_back(position);
    }
}

bool BasePiece::positionExists(const sf::Vector2f &position, const std::vector<sf::Vector2f> &positions) {
    for (const auto &pos : positions) {
        if (pos == position) {
            return true;
        }
    }
    return false;
}

bool BasePiece::isWithinBounds(const sf::Vector2f& position) {
    int size = block1.getSize().x;
    int minX, maxX, minY = 100, maxY = 1000;

    if (playerID == 1) {
        minX = 300;
        maxX = 300 + 10 * 40;
    } else {
        minX = 1300;
        maxX = 1300 + 10 * 40;
    }

    return position.x >= minX && position.x + size <= maxX && position.y >= minY && position.y + size <= maxY;
}

void BasePiece::land() {
    addPosition(block1.getPosition(), landedPositions);
    addPosition(block2.getPosition(), landedPositions);
    addPosition(block3.getPosition(), landedPositions);
    addPosition(block4.getPosition(), landedPositions);
    landed = true;
    movingDown = false;

    score += 1;  //increase score when the piece lands
    clearFullRows(landedPositions, score);
}

int BasePiece::clearFullRows(std::vector<sf::Vector2f>& landedPositions, int& score) {
    std::map<int, int> rowCounts;
    for (const auto& pos : landedPositions) {
        rowCounts[static_cast<int>(pos.y)]++;
    }

    std::vector<int> clearedRows;
    for (const auto& rowCount : rowCounts) {
        if (rowCount.second >= 10) {
            clearedRows.push_back(rowCount.first);
        }
    }

    if (!clearedRows.empty()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("Sound/clear.wav")) {
            std::cerr << "Failed to load clear.wav" << std::endl;
            return -1;
        }

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(25);
        sound.play();

        // Wait while the sound is playing.
        while (sound.getStatus() == sf::Sound::Playing) {
            sf::sleep(sf::milliseconds(100));
        }
    }

    std::vector<sf::Vector2f> newLandedPositions;
    for (const auto& pos : landedPositions) {
        if (std::find(clearedRows.begin(), clearedRows.end(), static_cast<int>(pos.y)) == clearedRows.end()) {
            newLandedPositions.push_back(pos);
        }
    }

    std::sort(clearedRows.begin(), clearedRows.end());
    for (auto& pos : newLandedPositions) {
        for (int clearedRow : clearedRows) {
            if (pos.y < clearedRow) {
                pos.y += 40;
            }
        }
    }

    landedPositions = newLandedPositions;

    int linesCleared = clearedRows.size();
    switch (linesCleared) {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
    }

    return linesCleared;
}

void BasePiece::fastDropController(int playerID) {
    const sf::Time fastDropInterval = sf::milliseconds(50);
    const int fastDropSpeed = 40;

    float dpadY = sf::Joystick::getAxisPosition(playerID, sf::Joystick::PovY);

    if (dpadY < -50) {
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

void BasePiece::moveController(int playerID) {
    if (landed || movingDown || fastDropping) return;

    float dpadX = sf::Joystick::getAxisPosition(playerID, sf::Joystick::PovX);

    const float Movement_Speed = 40;
    if (movementClock.getElapsedTime() > sf::milliseconds(50)) {
        if (dpadX > 50 && !checkCollision(Movement_Speed, 0)) {
            block1.move(Movement_Speed, 0);
            block2.move(Movement_Speed, 0);
            block3.move(Movement_Speed, 0);
            block4.move(Movement_Speed, 0);
        }
        if (dpadX < -50 && !checkCollision(-Movement_Speed, 0)) {
            block1.move(-Movement_Speed, 0);
            block2.move(-Movement_Speed, 0);
            block3.move(-Movement_Speed, 0);
            block4.move(-Movement_Speed, 0);
        }
        movementClock.restart();
    }
}