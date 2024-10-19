#include "../Headers/BasePiece.h"
#include <iostream>

extern bool playerCanPlay[2];

BasePiece::BasePiece(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score)
        : landedPositions(positions), playerID(playerID), drop_speed(0, 40), score(score), landed(false) {
    block1 = sf::RectangleShape(sf::Vector2f(size, size));
    block2 = sf::RectangleShape(sf::Vector2f(size, size));//makes the four block for a shape
    block3 = sf::RectangleShape(sf::Vector2f(size, size));
    block4 = sf::RectangleShape(sf::Vector2f(size, size));

    block1.setTexture(&texture);//sets the texture for the blocks
    block2.setTexture(&texture);
    block3.setTexture(&texture);
    block4.setTexture(&texture);

    block1.setPosition(x, y);
    block2.setPosition(x + size, y);//sets up the formation of the blocks to make a shape
    block3.setPosition(x, y + size);
    block4.setPosition(x + size, y + size);
}

void BasePiece::move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight) {
    if (landed || movingDown || fastDropping) return;

    const float Movement_Speed = 40; //move 40 pixels, one block size if movement is detected
    if (movementClock.getElapsedTime() > sf::milliseconds(50)) { //if moving side to side, movement will occur every 50 ms if holding down.
        if (sf::Keyboard::isKeyPressed(moveRight) && !checkCollision(Movement_Speed, 0)) {
            block1.move(Movement_Speed, 0);//moves 40 pixels to the right
            block2.move(Movement_Speed, 0);
            block3.move(Movement_Speed, 0);
            block4.move(Movement_Speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(moveLeft) && !checkCollision(-Movement_Speed, 0)) {
            block1.move(-Movement_Speed, 0);//moves 40 pixels to the left
            block2.move(-Movement_Speed, 0);
            block3.move(-Movement_Speed, 0);
            block4.move(-Movement_Speed, 0);
        }
        movementClock.restart();
    }
}

void BasePiece::fastDrop(sf::Keyboard::Key fastDropKey) {
    const sf::Time fastDropInterval = sf::milliseconds(50);//when dropping fast it drops 40 pixels evey 50 ms
    const int fastDropSpeed = 40;

    if (sf::Keyboard::isKeyPressed(fastDropKey)) {
        fastDropping = true;
        if (dropClock.getElapsedTime() >= fastDropInterval) {
            if (landed) return;//if the block is landed dont drop further

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


void BasePiece::drop(bool &InMenu) {
    if(!InMenu){
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
            land(); //land if it doesn't move down
        }

        dropClock.restart();
        }
    }
}


void BasePiece::draw(sf::RenderWindow& window, const sf::Texture& texture) {//draw the blocks
    sf::Vector2f blockSize(40, 40);
    for (const auto& pos : landedPositions) {
        sf::RectangleShape block(blockSize);
        block.setPosition(pos);
        block.setTexture(&texture);
        window.draw(block);
    }

    if (!landed) {
        if (block1.getPosition().y >= 200) window.draw(block1);
        if (block2.getPosition().y >= 200) window.draw(block2);
        if (block3.getPosition().y >= 200) window.draw(block3);
        if (block4.getPosition().y >= 200) window.draw(block4);
    }
}

bool BasePiece::checkCollision(float dx, float dy) {//checks collisions inside the layouts
    int minX = 0, maxX = 0;

    if (playerID == 1) {//player one has boundries 300 and 660 x
        minX = 300;
        maxX = 660;
    } else if (playerID == 2 && playerCanPlay[1]) {//player 2 has these boundries if its multiplayer
        minX = 1300;
        maxX = 1660;
    } else if (playerID == 2 && !playerCanPlay[1]) {//theseboundries if singleplayer
        minX = 800;
        maxX = 1160;
    }



    for (const auto &pos : landedPositions) {
        if ((block1.getPosition().x + dx == pos.x && block1.getPosition().y + dy == pos.y) ||
            (block2.getPosition().x + dx == pos.x && block2.getPosition().y + dy == pos.y) ||
            (block3.getPosition().x + dx == pos.x && block3.getPosition().y + dy == pos.y) ||
            (block4.getPosition().x + dx == pos.x && block4.getPosition().y + dy == pos.y)) {
            std::cout << "Collision with landed position at: " << pos.x << ", " << pos.y << std::endl;
            return true;
        }
    }


    if ((dx > 0 && (block1.getPosition().x + dx > maxX || block2.getPosition().x + dx > maxX ||
                    block3.getPosition().x + dx > maxX || block4.getPosition().x + dx > maxX)) ||
        (dx < 0 && (block1.getPosition().x + dx < minX || block2.getPosition().x + dx < minX ||
                    block3.getPosition().x + dx < minX || block4.getPosition().x + dx < minX))) {
        std::cout << "Collision with horizontal boundary" << std::endl;
        return true;
    }

    if (dy > 0 && (block1.getPosition().y + dy + block1.getSize().y > 1000 ||
                   block2.getPosition().y + dy + block2.getSize().y > 1000 ||
                   block3.getPosition().y + dy + block3.getSize().y > 1000 ||
                   block4.getPosition().y + dy + block4.getSize().y > 1000)) {
        std::cout << "Collision with bottom boundary" << std::endl;
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

bool BasePiece::isWithinBounds(const sf::Vector2f& position) {//checks if the blocks will be withing the layout after rotating
    int size = block1.getSize().x;
    int minX, maxX, minY = 100, maxY = 1000;

    if (playerID == 1) {
        minX = 300;
        maxX = 660;
    } else if (playerID == 2 && playerCanPlay[1]) {
        minX = 1300;
        maxX = 1660;
    } else if (playerID == 2 && !playerCanPlay[1]) {
        minX = 800;
        maxX = 1160;
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

    if (!clearedRows.empty()) {//adds a sound for clearing rows
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("Sound/clear.wav")) {
            std::cerr << "Failed to load clear.wav" << std::endl;
            return -1;
        }

        sf::Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(75);
        sound.play();

        //wait while the sound is playing.
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
    //score system
    int linesCleared = clearedRows.size();//the score system based on how many lines cleared
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

void BasePiece::fastDropController(int playerID) {//fastdropping for controller
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

void BasePiece::moveController(int playerID) {//movement for controller
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