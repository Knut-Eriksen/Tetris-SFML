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
