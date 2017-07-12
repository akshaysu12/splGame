#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP

#include "initGame.hpp"
#include <vector>
#include <iostream>

//Function Headers
void buy(Board* gameBoard, Player* currPlayer, int row, int column);
void reserve(Board* gameBoard, Player* currPlayer, int row, int column);
int getTokens(Board* gameBoard, Player* currPlayer, int *toGrab);
void show(Player* currPlayer);
void showAll(Board* gameBoard, int numPlayers);
void help();
void endOfTurn(Board* gameBoard, Player* &currPlayer, bool &endTurn, int numPlayers, int &currPos, bool &endGame);
bool endOfGame(Player* currPlayer);

#endif
