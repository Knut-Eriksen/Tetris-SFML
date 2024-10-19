#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <ctime>
#include "Headers and cpp files/Headers/functions.h"
#include "Headers and cpp files/Headers/BasePiece.h"
#include "Headers and cpp files/Headers/Menu.h"

std::vector<sf::Vector2f> landedPositionsP1, landedPositionsP2;
int scorePlayer1 = 0, scorePlayer2 = 0;
bool playerCanPlay[2] = {false, false};
bool singleplayer = true;
std::string winnerMessage = "";
sf::Text winnerText;

//resets game state after game over
void resetGameState(std::vector<std::unique_ptr<BasePiece>> &piecesP1, std::vector<std::unique_ptr<BasePiece>> &piecesP2, bool &gameOverP1, bool &gameOverP2, bool &pause1, bool &pause2, bool &initialSpawnDone, bool &inMenu, Menu &menu) {
    piecesP1.clear();
    piecesP2.clear();
    landedPositionsP1.clear();
    landedPositionsP2.clear();
    scorePlayer1 = 0;
    scorePlayer2 = 0;
    gameOverP1 = false;
    gameOverP2 = false;
    pause1 = false;
    pause2 = false;
    playerCanPlay[0] = false;
    playerCanPlay[1] = false;
    singleplayer = true;
    initialSpawnDone = false;
    inMenu = true;
    menu.resetMenu();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(2000, 1200), "Tetris");//makes the window

    sf::Joystick::Identification id = sf::Joystick::getIdentification(0);

    bool connected = sf::Joystick::isConnected(0);

    unsigned int buttons = sf::Joystick::getButtonCount(0);

    std::cout << "Joystick ID: " << id.name.toAnsiString() << std::endl;
    std::cout << "Vendor ID: " << id.vendorId << std::endl;
    std::cout << "Product ID: " << id.productId << std::endl;

    std::cout << "Is Connected: " << (connected ? "Yes" : "No") << std::endl;

    Menu menu(window.getSize().x, window.getSize().y);

    bool inMenu = true;

    sf::Texture texture;
    if (!texture.loadFromFile("Textures/I_O_T_greenblock.png")) {//adds block textures
        std::cerr << "Failed to load texture!" << std::endl;
        return 1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Textures/NES_Background.png")) {//adds the background
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }

    //adds the music
    sf::Music music;
    if (!music.openFromFile("Sound/Music.ogg")) return -1;
    music.setVolume(40);
    music.setLoop(true);
    music.play();

    //this is the font
    sf::Font font;
    if (!font.loadFromFile("Textures/Tetris.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    winnerText.setFont(font);
    winnerText.setCharacterSize(50);
    winnerText.setFillColor(sf::Color::Red);
    winnerText.setStyle(sf::Text::Bold);

    sf::SoundBuffer menuSelectBuffer;//the movement sound in the menu
    if (!menuSelectBuffer.loadFromFile("Sound/menu_select.wav")) {
        std::cerr << "Failed to load menu select sound!" << std::endl;
        return 1;
    }

    sf::Sound menuSelectSound;
    menuSelectSound.setBuffer(menuSelectBuffer);

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

    if (!inMenu) {
        if (playerCanPlay[1]) {
            spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1,
                           scorePlayer1);
            spawnNextBlock(piecesP2, texture, landedPositionsP2, 1500, 200, 2, currentBlockTypeP2, nextBlockTypeP2,
                           scorePlayer2);
        } else {
            spawnNextBlock(piecesP2, texture, landedPositionsP2, 1000, 200, 2, currentBlockTypeP2, nextBlockTypeP2,
                           scorePlayer2);
        }
    }

    nextBlockTypeP1 = rand() % 7;//random selection of 7 different blocks
    nextBlockTypeP2 = rand() % 7;
    currentBlockTypeP1 = nextBlockTypeP1;//after the block before is landed, the nextblock is moved to currentblocktype.
    currentBlockTypeP2 = nextBlockTypeP2;

    bool initialSpawnDone = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {//event loop
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (inMenu) {
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            menu.moveUp();
                            menuSelectSound.play();
                            break;
                        case sf::Keyboard::Down:
                            menu.moveDown();
                            menuSelectSound.play();
                            break;
                        case sf::Keyboard::Enter:
                            int selectedIndex = menu.getSelectedIndex();
                            if (selectedIndex == 1 && !menu.PlayPressed) {
                                menu.PlayPressed = true;
                                menu.updateMenu();
                            } else if (selectedIndex == 1 && menu.PlayPressed) {
                                //Singleplayer Mode
                                inMenu = false;
                                singleplayer = true;
                                playerCanPlay[0] = true;
                                playerCanPlay[1] = false;

                                spawnNextBlock(piecesP2, texture, landedPositionsP2, 1000, 200, 2, currentBlockTypeP2,//spawns the blocks inside event loop first
                                               nextBlockTypeP2, scorePlayer2);

                                initialSpawnDone = true;
                            } else if (selectedIndex == 2 && menu.PlayPressed) {
                                //Multiplayer Mode
                                inMenu = false;
                                singleplayer = false;
                                playerCanPlay[0] = true;
                                playerCanPlay[1] = true;

                                spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1,
                                               nextBlockTypeP1, scorePlayer1);
                                spawnNextBlock(piecesP2, texture, landedPositionsP2, 1500, 200, 2, currentBlockTypeP2,
                                               nextBlockTypeP2, scorePlayer2);

                                initialSpawnDone = true;
                            } else if (selectedIndex == 2 && !menu.PlayPressed) {
                                window.close();
                            }
                            menuSelectSound.play();
                            break;
                    }
                }
            } else {
                if (event.type == sf::Event::KeyPressed) {//movement or keyboard
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
                            for (auto &piece: piecesP1) piece->move(sf::Keyboard::A, sf::Keyboard::D);
                            break;
                        case sf::Keyboard::Left:
                        case sf::Keyboard::Right:
                            for (auto &piece: piecesP2) piece->move(sf::Keyboard::Left, sf::Keyboard::Right);
                            break;
                    }
                }

                if (event.type == sf::Event::JoystickMoved) {//joystick moving
                    std::cout << "Joystick Moved: " << event.joystickMove.joystickId << " Axis: "
                              << event.joystickMove.axis << " Position: " << event.joystickMove.position << std::endl;
                    if (event.joystickMove.axis == sf::Joystick::PovX) {
                        if (event.joystickMove.joystickId == 0) {
                            for (auto &piece: piecesP1) piece->moveController(0);
                        }
                        if (event.joystickMove.joystickId == 1) {
                            for (auto &piece: piecesP2) piece->moveController(1);
                        }
                    }
                }

                if (event.type == sf::Event::JoystickButtonPressed) {//controller buttons
                    std::cout << "Joystick Button Pressed: " << event.joystickButton.joystickId << " Button: "
                              << event.joystickButton.button << std::endl;
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
            if (!playerCanPlay[1]) {
                winnerMessage = "Player 2 Score: " + std::to_string(scorePlayer2);

                winnerText.setString(winnerMessage);
                winnerText.setPosition(window.getSize().x / 2 - winnerText.getGlobalBounds().width / 2, window.getSize().y / 2);

                std::cout << "Winner Message: " << winnerMessage << std::endl;

                resetGameState(piecesP1, piecesP2, gameOverP1, gameOverP2, pause1, pause2, initialSpawnDone, inMenu, menu);
                continue;
            }
        }

        if (!singleplayer && gameOverP1 && gameOverP2) {
            std::cout << "Game Over" << std::endl;

            if (scorePlayer1 > scorePlayer2) {
                winnerMessage = "Player 1 Wins!";
            } else if (scorePlayer2 > scorePlayer1) {
                winnerMessage = "Player 2 Wins!";
            } else {
                winnerMessage = "It's a Tie!";
            }

            winnerText.setString(winnerMessage);
            winnerText.setPosition(window.getSize().x / 2 - winnerText.getGlobalBounds().width / 2, window.getSize().y / 2);

            std::cout << "Winner Message: " << winnerMessage << std::endl;

            resetGameState(piecesP1, piecesP2, gameOverP1, gameOverP2, pause1, pause2, initialSpawnDone, inMenu, menu);
            continue;
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
            spawnNextBlock(piecesP1, texture, landedPositionsP1, 500, 200, 1, currentBlockTypeP1, nextBlockTypeP1,
                           scorePlayer1);
        }
        if (initialSpawnDone && allBlocksLanded(piecesP2) && !pause2) {
            spawnNextBlock(piecesP2, texture, landedPositionsP2, playerCanPlay[1] ? 1500 : 1000, 200, 2,
                           currentBlockTypeP2, nextBlockTypeP2, scorePlayer2);
        }

        if (inMenu) {
            menu.draw(window);
            if (!winnerMessage.empty()) {
                sf::Text winnerText;
                winnerText.setFont(font);
                winnerText.setString(winnerMessage);
                winnerText.setCharacterSize(50);
                winnerText.setFillColor(sf::Color::Red);
                winnerText.setStyle(sf::Text::Bold);
                winnerText.setPosition(window.getSize().x / 2 - winnerText.getGlobalBounds().width / 2,
                                       window.getSize().y / 2 - 100);
                window.draw(winnerText);
            }
        } else {
            if (playerCanPlay[1]) {
                drawNextBlock(window, texture, nextBlockTypeP1, sf::Vector2f(150, 600));
                drawNextBlock(window, texture, nextBlockTypeP2, sf::Vector2f(1825, 600));
            }

            if (!playerCanPlay[1]) {
                drawNextBlock(window, texture, nextBlockTypeP2, sf::Vector2f(1325, 600));
            }
        }

        if (playerCanPlay[1]) {
            for (auto &piece: piecesP1) piece->draw(window, texture);
        }
        for (auto &piece: piecesP2) piece->draw(window, texture);

        if (!inMenu) {
            drawScores(window, font, scorePlayer1, scorePlayer2);
        }

        window.display();
    }
}