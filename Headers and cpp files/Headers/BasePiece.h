#ifndef TETRIS_SFML_BASEPIECE_H
#define TETRIS_SFML_BASEPIECE_H

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>


class BasePiece {
public:
    //~BasePiece is a destructor. It is called when an object of the class is destroyed. Cleans up memory
    //virtual means the destructor can be overridden in derived classes: I, J, L, O, S, T and Z
    //eg 'void rotate() override;' in I.h, then void I::rotate() {'rotation code for I'}
    virtual ~BasePiece() = default;
    virtual void rotateClockWise() {}; //used by J, L and T
    virtual void rotateCounterClockWise() {}; //used by J, L and T
    virtual void rotate() {}; //used by I, S and Z

    void draw(sf::RenderWindow& window, const sf::Texture& texture);
    void fastDropController(int playerID);
    void moveController(int playerID);
    void move(sf::Keyboard::Key moveLeft, sf::Keyboard::Key moveRight);
    void fastDrop(sf::Keyboard::Key fastDropKey);
    void drop(bool &InMenu);

    bool isLanded() const {
        return landed;
    }




protected:

    bool singleplayer = true;
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
