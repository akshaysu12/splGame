#ifndef DRAW_HPP
#define DRAW_HPP

#include "playGame.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

void makeGridLine();
void printHeadCell(std::string content);
void printBodyCell(std::string content);
void showBoard(Board* gameBoard);

#endif
