#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <ctime>
#include "Headers and cpp files/Headers/O.h"
#include "Headers and cpp files/Headers/functions.h"

//define global variables for landed positions and scores
std::vector<sf::Vector2f> landedPositionsP1, landedPositionsP2;
int scorePlayer1 = 0, scorePlayer2 = 0;

int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1200), "Tetris");
    sf::Texture texture;
    if (!texture.loadFromFile("Textures/Block.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return 1;
    }

    sf::Music music;
    if (!music.openFromFile("Sound/Music.ogg")) return -1;
    music.setVolume(5);
    music.play();

    sf::Font font;
    if (!font.loadFromFile("Textures/Tetris.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<BasePiece>> piecesP1, piecesP2;

    srand(static_cast<unsigned int>(time(nullptr)));

    bool gameOverP1 = false, gameOverP2 = false;
    bool pause1 = false, pause2 = false;
    int currentBlockTypeP1, nextBlockTypeP1 = rand() % 7;
    int currentBlockTypeP2, nextBlockTypeP2 = rand() % 7;

    spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1, scorePlayer1);
    spawnNextBlock(piecesP2, texture, landedPositionsP2, 1500, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::X:
                        handleRotation(piecesP1, true);
                        break;
                    case sf::Keyboard::Z:
                        handleRotation(piecesP1, false);
                        break;
                    case sf::Keyboard::M:
                        handleRotation(piecesP2, true);
                        break;
                    case sf::Keyboard::N:
                        handleRotation(piecesP2, false);
                        break;
                    case sf::Keyboard::A:
                    case sf::Keyboard::D:
                        for (auto &piece : piecesP1) piece->move(sf::Keyboard::A, sf::Keyboard::D);
                        break;
                    case sf::Keyboard::Left:
                    case sf::Keyboard::Right:
                        for (auto &piece : piecesP2) piece->move(sf::Keyboard::Left, sf::Keyboard::Right);
                        break;
                }
            }
        }

        if (checkGameOver(landedPositionsP1) && !pause1) {
            std::cout << "Player 1 game over" << std::endl;
            gameOverP1 = true;
            pause1 = true;
        }

        if (checkGameOver(landedPositionsP2) && !pause2) {
            std::cout << "Player 2 game over" << std::endl;
            gameOverP2 = true;
            pause2 = true;
        }

        if (gameOverP1 && gameOverP2) {
            std::cout << "Game Over" << std::endl;
            break;
        }

        for (auto &piece : piecesP1) {
            piece->drop();
            piece->fastDrop(sf::Keyboard::S);
        }
        for (auto &piece : piecesP2) {
            piece->drop();
            piece->fastDrop(sf::Keyboard::Down);
        }

        if (allBlocksLanded(piecesP1)) {
            if (!gameOverP1) {
                spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1, scorePlayer1);
            }
        }
        if (allBlocksLanded(piecesP2)) {
            if (!gameOverP2) {
                spawnNextBlock(piecesP2, texture, landedPositionsP2, 1500, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);
            }
        }

        window.clear(sf::Color::White);
        layout(window);

        drawNextBlock(window, texture, nextBlockTypeP1, sf::Vector2f(50, 600));
        drawNextBlock(window, texture, nextBlockTypeP2, sf::Vector2f(1850, 600));

        for (auto &piece : piecesP1) piece->draw(window);
        for (auto &piece : piecesP2) piece->draw(window);

        drawScores(window, font, scorePlayer1, scorePlayer2);

        window.display();
    }

    return 0;
}
