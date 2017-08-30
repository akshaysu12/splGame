#ifndef BOTPLAYER_HPP
#define BOTPLAYER_HPP

#include "playGame.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void botTurn(Board* gameBoard, Player *currPlayer);
void botBuy(Board* gameBoard, Player *currPlayer, Card* cardWanted, int row, int column);
void grabTokens(Board* gameBoard, Player *currPlayer, int* supply, int botGrab[]);

#endif
