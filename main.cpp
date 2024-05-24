#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <ctime>
#include "Headers and cpp files/Headers/functions.h"
#include "Headers and cpp files/Headers/BasePiece.h"
#include "Headers and cpp files/Headers/Menu.h"

// define global variables for landed positions and scores
std::vector<sf::Vector2f> landedPositionsP1, landedPositionsP2;
int scorePlayer1 = 0, scorePlayer2 = 0;
bool playerCanPlay[2] = {false, false};

int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1200), "Tetris");

    Menu menu(window.getSize().x, window.getSize().y);

    bool inMenu = true;

    sf::Texture texture;
    if (!texture.loadFromFile("Textures/Block.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return 1;
    }

    // Load the background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Textures/NES_Background.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }

    sf::Music music;
    if (!music.openFromFile("Sound/Music.ogg")) return -1;
    music.setVolume(5);
    music.setLoop(true);
    music.play();

    sf::Font font;
    if (!font.loadFromFile("Textures/Tetris.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    // Create a sprite for the background
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundSprite.getGlobalBounds().width,
            static_cast<float>(window.getSize().y) / backgroundSprite.getGlobalBounds().height
    );

    std::vector<std::unique_ptr<BasePiece>> piecesP1, piecesP2;

    srand(static_cast<unsigned int>(time(nullptr)));

    bool gameOverP1 = false, gameOverP2 = false;
    bool pause1 = false, pause2 = false;

    int currentBlockTypeP1, nextBlockTypeP1;
    int currentBlockTypeP2, nextBlockTypeP2;


    // Ensure the blocks are spawned according to game mode
    if (playerCanPlay[1]) {
        spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1, scorePlayer1);
        spawnNextBlock(piecesP2, texture, landedPositionsP2, 1500, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);
    } else {
        spawnNextBlock(piecesP2, texture, landedPositionsP2, 1000, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);
    }

    nextBlockTypeP1 = rand() % 7;
    nextBlockTypeP2 = rand() % 7;
    currentBlockTypeP1 = nextBlockTypeP1;
    currentBlockTypeP2 = nextBlockTypeP2;

    bool initialSpawnDone = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (inMenu) {
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.moveUp();
                            break;
                        case sf::Keyboard::Down:
                            menu.moveDown();
                            break;
                        case sf::Keyboard::Enter:
                            int selectedIndex = menu.getSelectedIndex();
                            if (selectedIndex == 1 && !menu.PlayPressed) {
                                menu.PlayPressed = true;
                                menu.updateMenu();
                            } else if (selectedIndex == 1) {
                                inMenu = false;
                                playerCanPlay[1] = false;
                                playerCanPlay[0] = true;
                                spawnNextBlock(piecesP2, texture, landedPositionsP2, 1000, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);

                                initialSpawnDone = true;
                            } else if (selectedIndex == 2 && menu.PlayPressed) {
                                inMenu = false;
                                playerCanPlay[1] = true;
                                playerCanPlay[0] = true;
                                spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1, scorePlayer1);
                                spawnNextBlock(piecesP2, texture, landedPositionsP2, 1500, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);
                                initialSpawnDone = true;
                            } else if (selectedIndex == 2 && !menu.PlayPressed) {
                                window.close();
                            }
                            break;
                    }
                }
            } else {
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

                if (event.type == sf::Event::JoystickMoved) {
                    if (event.joystickMove.axis == sf::Joystick::PovX) {
                        if (event.joystickMove.joystickId == 0) {
                            for (auto &piece : piecesP1) piece->moveController(0);
                        }
                        if (event.joystickMove.joystickId == 1) {
                            for (auto &piece : piecesP2) piece->moveController(1);
                        }
                    }
                }

                if (event.type == sf::Event::JoystickButtonPressed) {
                    if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 0) {
                        handleRotation(piecesP1, false);
                    }

                    if (event.joystickButton.joystickId == 0 && event.joystickButton.button == 1) {
                        handleRotation(piecesP1, true);
                    }

                    if (event.joystickButton.joystickId == 1 && event.joystickButton.button == 0) {
                        handleRotation(piecesP2, false);
                    }

                    if (event.joystickButton.joystickId == 1 && event.joystickButton.button == 1) {
                        handleRotation(piecesP2, true);
                    }
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

        if (!inMenu) {
            if (playerCanPlay[1]) {
                for (auto &piece: piecesP1) {
                    piece->drop(inMenu);
                    piece->fastDrop(sf::Keyboard::S);
                    piece->fastDropController(0);
                }
            }
            for (auto &piece: piecesP2) {
                piece->drop(inMenu);
                piece->fastDrop(sf::Keyboard::Down);
                piece->fastDropController(1);
            }
        }

        window.clear();
        window.draw(backgroundSprite);

        if (!inMenu && playerCanPlay[1])
            layout(window);
        else if (!inMenu && !playerCanPlay[1])
            layoutSingleplayer(window);

        if (initialSpawnDone && allBlocksLanded(piecesP1) && !pause1) {
            spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1, scorePlayer1);

        }
        if (initialSpawnDone && allBlocksLanded(piecesP2) && !pause2) {
            spawnNextBlock(piecesP2, texture, landedPositionsP2, playerCanPlay[1] ? 1500 : 1000, 200, 2, currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);
        }

        if (inMenu) {
            menu.draw(window);
        } else {
            drawNextBlock(window, texture, nextBlockTypeP1, sf::Vector2f(50, 600));
            drawNextBlock(window, texture, nextBlockTypeP2, sf::Vector2f(1850, 600));
        }

        if (playerCanPlay[1]) {
            for (auto &piece: piecesP1) piece->draw(window, texture);
        }
        for (auto &piece : piecesP2) piece->draw(window, texture);

        drawScores(window, font, scorePlayer1, scorePlayer2);

        window.display();
    }

    return 0;
}