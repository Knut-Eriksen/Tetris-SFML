//
// Created by mhjul on 18.05.2024.
//

#ifndef TETRIS_SFML_BASEPIECE_H
#define TETRIS_SFML_BASEPIECE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>

class BasePiece {
public:
    virtual ~BasePiece() = default;
    virtual void rotateClockWise() = 0;
    virtual void rotateCounterClockWise() = 0;
    virtual void rotate() = 0;

    void draw(sf::RenderWindow& window);
    void move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight);
    void fastDrop(sf::Keyboard::Key fastDropKey);
    void drop();

    bool isLanded() const {
        return landed;
    }



protected:
    sf::RectangleShape block1, block2, block3, block4;
    sf::Vector2f drop_speed;
    sf::Clock dropClock, movementClock;
    bool landed = false;
    bool movingDown = false;
    bool fastDropping = false;
    std::vector<sf::Vector2f>& landedPositions;
    int playerID;
    int& score;


    BasePiece(const sf::Texture &texture, std::vector<sf::Vector2f>& positions, int size, int x, int y, int playerID, int& score);

    bool checkCollision(float dx, float dy);
    void addPosition(const sf::Vector2f &position, std::vector<sf::Vector2f> &positions);
    bool positionExists(const sf::Vector2f &position, const std::vector<sf::Vector2f> &positions);
    bool isWithinBounds(const sf::Vector2f& position);
    void land();
    int clearFullRows(std::vector<sf::Vector2f>& landedPositions, int& score);
};

#endif //TETRIS_SFML_BASEPIECE_H
