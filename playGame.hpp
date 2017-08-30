#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP

#include "initGame.hpp"
#include <vector>
#include <iostream>

//Function Headers
int buy(Board* gameBoard, Player* currPlayer, int row, int column);
int reserve(Board* gameBoard, Player* currPlayer, int row, int column);
int getTokens(Board* gameBoard, Player* currPlayer, int *toGrab);
void show(Player* currPlayer);
void showAll(Board* gameBoard, std::vector<Player> *players);
void help();
void endOfTurn(Board* gameBoard, Player* &currPlayer, bool &endTurn, int numPlayers, int &currPos, bool &endGame);
bool endOfGame(Player* currPlayer);
void play(std::vector<std::string> names);
void rules();
void resign(Board* gameBoard, Player* &currPlayer, bool &endTurn, int numPlayers, int &currPos, bool &endGame);

#endif
