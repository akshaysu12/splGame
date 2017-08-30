#include "botPlayer.hpp"
#include "draw.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**************
0. If bot has a reserved card buy it
1. If card is available to buy, buy it - buy first possible card.
2. If there is a card that is available with only resources but short one, reserve it
3. Calculate the differences between bonuses+tokens and cost
  3a. If there is a cost that requires grabbing two, grab two of the that token
  3b. if there are no costs that require more than 1, grab 1 of as many as needed.
    b1. If there are extra tokens to grab, grab extras from the left. (or random?)
**************/
void botTurn(Board* gameBoard, Player *currPlayer)
{
  /*
  TO-ADD: BOT'S ABILITY TO RESERVE
  //buy reserved card if available
  if (!currPlayer->reservedCards.empty()) {
    buyReserved(currPlayer->reservedCards[0]);
    return;
  }
  */

  //std::vector<Card*> botFour = retrieveCards(gameBoard);

  //get board supply
  int* supply = gameBoard->getSupply();

  //get resources available for player
  int* playerTokens = currPlayer->getTokens();
  int* playerBonuses = currPlayer->showResources();
  int totalResources[5];
  for (int i = 0; i < 5; i++) {
    totalResources[i] = playerTokens[i] + playerBonuses[i];
  }

/***** There has to be a better way to do this - high priority for refactoring ******/
  int costDiff[5];
  int currDiffs[5];
  int smallestDiff = 1000;

  //check if any of the four cheapest cards can be bought
  //simultaneously keep track of which of the cards bot is closest to buying
  int cardsChecked = 0;
  int row = 0;
  int col = 0;
  while (cardsChecked < 4) {
    int diffSum = 0;
    Card* cardptr = gameBoard->getCard(row, col);
    int* cost = cardptr->getCost();
    //skip to next card without incrementing cardsChecked
    if (cardptr == nullptr) {
      if (col > 3) {
        col = 0;
        row++;
      }
      else
        col++;
      continue;
    }

    //check if the current card is able to be bought
    for (int j = 0; j < 5; j++) {
      if (cost[j] > totalResources[j]) {
        currDiffs[j] = cost[j] - totalResources[j];
        diffSum += currDiffs[j];
      }
      else
        currDiffs[j] = 0;
    }
    if (diffSum == 0) {
      botBuy(gameBoard, currPlayer, cardptr, row, col);
      return;
    }
    else
    {

      //figure out if this card is closer to being bought than current smallest
      if (diffSum < smallestDiff) {
        smallestDiff = diffSum;
        for (int i = 0; i < 5; i++) {
          costDiff[i] = currDiffs[i];
          //printf("cost diff at %d is %d\n", i, costDiff[i]);
        }
      }
    }

    //go to next card on gameboard
    if (col > 3) {
      col = 0;
      row++;
    }
    else
      col++;
    cardsChecked++;
  }

  //try to grab two tokens of one color
  for (int i = 0; i < 5; i++) {
    if (costDiff[i] > 1) {
      if (supply[i] < 5) {
        continue;
      }
      else {
        for (int j = 0; j < 5; j++) {
          if (j == i) {
            costDiff[j] = 2;
          }
          else
            costDiff[j] = 0;
        }
        grabTokens(gameBoard, currPlayer, supply, costDiff);
        return;
      }
    }
  }

  //else try to grab one token of three colors
  int count = 0;
  int currToken = 0;
  while (count < 3) {
    if (costDiff[currToken] > 0 && supply[currToken] > 0) {
      costDiff[currToken] = 1;
    }
    count++;
    currToken++;
  }
  grabTokens(gameBoard, currPlayer, supply, costDiff);
  return;
}


/*
TO ADD: BOT'S ABILITY TO RESERVE
//calculate what color the jester token will be used for.
//call buy function in playGame
void buyReserved()
{}
*/

//calculate row and column of the card to buy
//call buy function in playGame
void botBuy(Board* gameBoard, Player *currPlayer, Card* cardWanted, int row, int column)
{
  int success = currPlayer->buyCard(cardWanted);
  if (success == 1) {
    std::cout << "Bot successfully bought a card!" << std::endl;
    int* cost = cardWanted->getCost();
    gameBoard->addTokens(cost);
    gameBoard->replaceCard(row, column);
  }
}

// pass tokens to grab to gameRemoveTokens and playerAddTokens
void grabTokens(Board* gameBoard, Player *currPlayer, int* supply, int botGrab[])
{
  //for displaying what tokens the bot grabbed
  std::string *colors = gameBoard->getColors();

  gameBoard->removeTokens(botGrab);
  currPlayer->addTokens(botGrab);

  std::cout << std::endl;
  makeGridLine();
  std::cout << "|             " << "Bot has grabbed: ";
  for (int i = 0; i < 5; i++) {
      std::cout << botGrab[i] << ":" << colors[i] << " ";
  }
  std::cout << "tokens           |" << std::endl;
  makeGridLine();
  std::cout << std::endl;
  std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
  std::cin.ignore();
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}
