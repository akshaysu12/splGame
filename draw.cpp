#include "draw.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>


/****************
Interface Functions
*****************/

void makeGridLine()
{
  std::cout << " ";
  for (int i = 0; i < 83; i++) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

void printHeadCell(std::string content) {
  std::cout << "|" << " " << std::left << std::setw(10) << content << "|";
}

void printBodyCell(std::string content) {
  std::cout << std::setw(3) << " " << std::setw(11) << content << std::setw(3) << " " << "|";
}

//total width = 83 chars
void showBoard(Board* gameBoard)
{
  makeGridLine();
  std::cout << "|" << std::setw(37) << " " << "GAMEBOARD" << std::setw(37) << " " << "|";
  std::cout << std::setw(6) << " " << "Supply" << std::setw(5) << " " << "|" << std::endl;
  std::cout << "|" << std::setw(18) << " " << " Coin Order: [ White  Black  Red  Blue  Green ]" << std::setw(18) << " " << "|";
  int* supply = gameBoard->getSupply();
  std::string supplyString = "[";
  supplyString = supplyString + std::to_string(supply[0]) + " " + std::to_string(supply[1]) + " " + std::to_string(supply[2]) + " " + std::to_string(supply[3]) + " " + std::to_string(supply[4]) + "]";
  printBodyCell(supplyString);
  std::cout << std::endl;
  makeGridLine(); //makes a horizontal line spanning the width of the grid
  printHeadCell("Nobles");
  std::cout << std::right << std::setw(72) << "|" << std::endl;
  makeGridLine(); //makes a horizontal line spanning the width of the grid
  int count = 0;
  for (int k = 3; k >= 0; k--) {

    if (k == 2) {
      printHeadCell("Cards ");
      std::cout << std::right << std::setw(72) << "|" << '\n';
      makeGridLine(); //makes a horizontal line spanning the width of the grid
    }
    if (k != 3) {
      printHeadCell("Card #: ");
      for (int i = 0; i < 4; i++) {
        printBodyCell(std::to_string(count));
        count++;
      }
      std::cout << std::endl;
    }
    printHeadCell("Points: ");
    for (int i = 0; i < 4; i++) {
      Card* curr = gameBoard->getCard(k,i);
      if (curr == nullptr)
        printBodyCell("None");
      else
        printBodyCell(std::to_string(curr->getPoints()));
    }

    std::cout << std::endl;
    printHeadCell("Resource: ");
    for (int i = 0; i < 4; i++) {
      Card* curr = gameBoard->getCard(k,i);
      if (curr == nullptr)
        printBodyCell("None");
      else
        printBodyCell(curr->getColor());
    }

    std::cout << std::endl;
    printHeadCell("Cost: ");
    for (int i = 0; i < 4; i++) {
      Card* curr = gameBoard->getCard(k,i);
      if (curr == nullptr) {
        printBodyCell("None");
      }
      else {
        int* cost = curr->getCost();
        std::string costString = "[";
        costString = costString + std::to_string(cost[0]) + " " + std::to_string(cost[1]) + " " + std::to_string(cost[2]) + " " + std::to_string(cost[3]) + " " + std::to_string(cost[4]) + "]";
        printBodyCell(costString);
      }
    }
    std::cout << std::endl;
    makeGridLine();
  }
}
