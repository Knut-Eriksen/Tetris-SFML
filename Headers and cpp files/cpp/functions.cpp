#include "../Headers/functions.h"

void layout(sf::RenderWindow& window) {
    int height = 10;
    int width = 20;
    float multiplier = 40;

    sf::RectangleShape layout1(sf::Vector2f(height * multiplier, width * multiplier));
    layout1.setFillColor(sf::Color::Black);
    layout1.setPosition(300, 200);

    sf::RectangleShape layout2(sf::Vector2f(height * multiplier, width * multiplier));
    layout2.setFillColor(sf::Color::Black);
    layout2.setPosition(1300, 200);

    window.draw(layout1);
    window.draw(layout2);
}

bool allBlocksLanded(const std::vector<std::unique_ptr<BasePiece>>& pieces) {
    for (const auto& piece : pieces) {
        if (!piece->isLanded()) return false;
    }
    return true;
}

void spawnNextBlock(std::vector<std::unique_ptr<BasePiece>>& pieces, sf::Texture& texture, std::vector<sf::Vector2f>& landedPositions, int x, int y, int playerID, int& currentBlockType, int& nextBlockType, int& score) {
    currentBlockType = nextBlockType;
    nextBlockType = rand() % 7;

    switch (currentBlockType) {
        case 0:
            pieces.push_back(std::make_unique<O>(texture, landedPositions, 40, x, y, playerID, score));
            break;
        case 1:
            pieces.push_back(std::make_unique<J>(texture, landedPositions, 40, x, y, playerID, score));
            break;
        case 2:
            pieces.push_back(std::make_unique<I>(texture, landedPositions, 40, x, y, playerID, score));
            break;
        case 3:
            pieces.push_back(std::make_unique<L>(texture, landedPositions, 40, x, y, playerID, score));
            break;
        case 4:
            pieces.push_back(std::make_unique<T>(texture, landedPositions, 40, x, y, playerID, score));
            break;
        case 5:
            pieces.push_back(std::make_unique<S>(texture, landedPositions, 40, x, y, playerID, score));
            break;
        case 6:
            pieces.push_back(std::make_unique<Z>(texture, landedPositions, 40, x, y, playerID, score));
            break;
    }
}


bool checkGameOver(const std::vector<sf::Vector2f>& positions) {
    for (const auto& pos : positions) {
        if (pos.y == 200) {
            return true;
        }
    }
    return false;
}

void drawScores(sf::RenderWindow& window, sf::Font& font, int scorePlayer1, int scorePlayer2) {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);

    scoreText.setString("Player 1 Score: " + std::to_string(scorePlayer1));
    scoreText.setPosition(400, 100);
    window.draw(scoreText);

    scoreText.setString("Player 2 Score: " + std::to_string(scorePlayer2));
    scoreText.setPosition(1400, 100);
    window.draw(scoreText);
}

void drawNextBlock(sf::RenderWindow& window, const sf::Texture& texture, int nextBlockType, sf::Vector2f position) {
    int size = 40;
    sf::RectangleShape block(sf::Vector2f(size, size));
    block.setTexture(&texture);

    switch (nextBlockType) {
        case 0: //O
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y + size);
            window.draw(block);
            block.setPosition(position.x + size, position.y + size);
            window.draw(block);
            break;
        case 1: //J
            block.setPosition(position.x - size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y + size);
            window.draw(block);
            break;
        case 2: //I
            block.setPosition(position.x - size, position.y);
            window.draw(block);
            block.setPosition(position.x - 2 * size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y);
            window.draw(block);
            break;
        case 3: //L
            block.setPosition(position.x - size, position.y + size);
            window.draw(block);
            block.setPosition(position.x - size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y);
            window.draw(block);
            break;
        case 4: //T
            block.setPosition(position.x + size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x + 2 * size, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y + size);
            window.draw(block);
            break;
        case 5: //S
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x + size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y + size);
            window.draw(block);
            block.setPosition(position.x - size, position.y + size);
            window.draw(block);
            break;
        case 6: //Z
            block.setPosition(position.x, position.y);
            window.draw(block);
            block.setPosition(position.x - size, position.y);
            window.draw(block);
            block.setPosition(position.x, position.y + size);
            window.draw(block);
            block.setPosition(position.x + size, position.y + size);
            window.draw(block);
            break;
    }
}

void handleRotation(std::vector<std::unique_ptr<BasePiece>>& pieces, bool clockwise) {
    for (auto& piece : pieces) {
        if (I* iPiece = dynamic_cast<I*>(piece.get())) {
            iPiece->rotate();
        } else if (S* sPiece = dynamic_cast<S*>(piece.get())) {
            sPiece->rotate();
        } else if (Z* zPiece = dynamic_cast<Z*>(piece.get())) {
            zPiece->rotate();
        }else if (clockwise) {
            piece->rotateClockWise();
        } else {
            piece->rotateCounterClockWise();
        }
    }
}