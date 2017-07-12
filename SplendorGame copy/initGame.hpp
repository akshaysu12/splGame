#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "Board.hpp"
#include <vector>

Board* initializeGame(std::vector<std::string> names);
void shift(std::vector<int> &costs, int* resource, int i);
void generateSet(int costs[], std::vector<Card* > &levelOneCards);
void printCost(Card curr);
std::vector<Card>* generateLevelOneCards();
std::vector<Card>* generateLevelTwoCards();
std::vector<Card>* generateLevelThreeCards();
std::vector<Card>* generateNobleCards();
int myrandom (int i);
void cleanUp(Board *gameboard);
#endif
