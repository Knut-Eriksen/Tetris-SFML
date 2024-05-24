#ifndef TETRIS_SFML_FUNCTIONS_H
#define TETRIS_SFML_FUNCTIONS_H

#include "O.h"
#include "J.h"
#include "I.h"
#include "L.h"
#include "T.h"
#include "S.h"
#include "Z.h"


#include "SFML/Graphics.hpp"

class BasePiece;

void layout(sf::RenderWindow& window);
void layoutSingleplayer(sf::RenderWindow& window);
bool allBlocksLanded(const std::vector<std::unique_ptr<BasePiece>>& pieces);
void spawnNextBlock(std::vector<std::unique_ptr<BasePiece>>& pieces, sf::Texture& texture, std::vector<sf::Vector2f>& landedPositions, int x, int y, int playerID, int& currentBlockType, int& nextBlockType, int& score);
bool checkGameOver(const std::vector<sf::Vector2f>& positions);
void drawScores(sf::RenderWindow& window, sf::Font& font, int scorePlayer1, int scorePlayer2);
void drawNextBlock(sf::RenderWindow& window, const sf::Texture& texture, int nextBlockType, sf::Vector2f position);
void handleRotation(std::vector<std::unique_ptr<BasePiece>>& pieces, bool clockwise);

extern bool playerCanPlay[2];
extern bool singlePlayerMode;

#endif //TETRIS_SFML_FUNCTIONS_H
