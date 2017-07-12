#include "playGame.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  std::string *colors = gameBoard->getColors();
  makeGridLine(); //makes a horizontal line spanning the width of the grid
  printHeadCell("Nobles");
  std::cout << std::right << std::setw(72) << "|";
  int* supply = gameBoard->getSupply();
  std::string supplyString = "[";
  supplyString = supplyString + std::to_string(supply[0]) + " " + std::to_string(supply[1]) + " " + std::to_string(supply[2]) + " " + std::to_string(supply[3]) + " " + std::to_string(supply[4]) + "]";
  printBodyCell(supplyString);
  std::cout << std::endl;
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

/***************
Player Actions
***************/

/************
removes card from the gameboard and adds it to player
*************/

//bypass rules and add as many tokens as you want (up to 7 to your hand)
void Add(Board* gameBoard, Player* currPlayer, int toAdd[])
{
  gameBoard->removeTokens(toAdd);
  currPlayer->addTokens(toAdd);
  std::string *colors = gameBoard->getColors();

  std::cout << "You have added: ";
  for (int i = 0; i < 5; i++) {
      std::cout << toAdd[i] << ":" << colors[i] << " ";
  }
  std::cout << "tokens" << std::endl;
}

void AddBonus(Board* gameBoard, Player* currPlayer, int toAdd[])
{
  currPlayer->addBonus(toAdd);
  std::string *colors = gameBoard->getColors();

  std::cout << "You have added: ";
  for (int i = 0; i < 5; i++) {
      std::cout << toAdd[i] << ":" << colors[i] << " ";
  }
  std::cout << "tokens" << std::endl;
}

void buy(Board* gameBoard, Player* currPlayer, int row, int column)
{
  std::cout << "called buy" << std::endl;

  Card* cardWanted = gameBoard->getCard(row, column);
  int success = currPlayer->buyCard(cardWanted);
  if (success == 1) {
    std::cout << "card successfully bought!" << std::endl;
    int* cost = cardWanted->getCost();
    gameBoard->addTokens(cost);
    gameBoard->replaceCard(row, column);
  }
  else {
    std::cout << "sorry, you are unable to purchase that card." << std::endl;
  }

}

void reserve(Board* gameBoard, Player* currPlayer, int row, int column)
{
  std::cout << "called reserve" << std::endl;

  std::vector<Card*> *reserved = currPlayer->getReservedCards();
  if (reserved->size() >= 3) {
    std::cout << "You cannot reserve any more cards." << '\n';
    return;
  }

  currPlayer->reserveCard(gameBoard->getCard(row,column));
  gameBoard->replaceCard(row, column);
  gameBoard->decrementYellow();
}

void claim(Player* currPlayer, int cardLocation, int tokenReplace)
{
  currPlayer->buyReserveCard(cardLocation, tokenReplace);
}

void showSupply(Board* gameBoard)
{
  int* supply = gameBoard->getSupply();
  for (int i = 0; i < 5; i++) {
    std::cout << supply[i] << " ";
  }
  std::cout << std::endl;
}

int getTokens(Board* gameBoard, Player* currPlayer, int toGrab[])
{
  int DBLcount = 0;
  int SGLcount = 0;
  int *supply = gameBoard->getSupply();
  std::string *colors = gameBoard->getColors();

  //validate the tokens that the user tried to grab (to-do: make this more efficient)
  for (int i = 0; i < 5; i++) {
    if (toGrab[i] > 1) {
      if (supply[i] < 4) {
        std::cout << "There are not enough tokens" << colors[i] << " tokens" << '\n';
        return -1;
      }
      DBLcount++;
    }
    if (DBLcount > 1) {
      std::cout << "Sorry. You can only grab one type of color if you are grabbing two tokens." << std::endl;
      return - 1;
    }

    if (toGrab[i] > 0) {
      SGLcount++;
    }
    if (SGLcount > 3) {
      std::cout << "Sorry. You can only grab 3 tokens if you are grabbing multiple colors." << std::endl;
      return -1;
    }
  }

  gameBoard->removeTokens(toGrab);
  currPlayer->addTokens(toGrab);

  std::cout << "You have grabbed: ";
  for (int i = 0; i < 5; i++) {
      std::cout << toGrab[i] << ":" << colors[i] << " ";
  }
  std::cout << "tokens" << std::endl;
  return 1;
}

void show(Player* currPlayer)
{
  std::cout << currPlayer->getName() << '\n';
  std::cout << "Points:" << currPlayer->getPoints() << '\n';
  std::cout << "Current Supply:" << '\n';
  int* tokens = currPlayer->getTokens();
  std::cout << "Tokens:" << "[" << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << " " << tokens[4] << "]" <<  '\n';
  int* resources = currPlayer->showResources();
  std::cout << "Resources:" << "[" << resources[0] << " " << resources[1] << " " << resources[2] << " " << resources[3] << " " << resources[4] << "]" <<  '\n';
  std::vector<Card*> *reserved = currPlayer->getReservedCards();
  if (reserved->size() > 0) {
    std::cout << "Reserved Cards: " << std::endl;
    for (int i = 0; i < reserved->size(); i++) {
      std::cout << "Reserved Card " << i << ":" << std::endl;
      int *cost = reserved->at(i)->getCost();
      std::cout << "Points:" << currPlayer->getPoints() << '\n';
      std::cout << "Cost:" << "[" << cost[0] << " " << cost[1] << " " << cost[2] << " " << cost[3] << " " << cost[4] << "]" <<  '\n';
      std::cout << std::endl;
    }
  }

}

void showAll(Board* gameBoard, int numPlayers)
{
  /*
  Player* players = gameBoard->getPlayers();
  for (int i = 0; i < numPlayers; i++) {
    show(players[i]);
  }
  */
  std::cout << "show all players here" << '\n';
}

void help()
{
  std::cout << "show help keywords here" << '\n';
}

void endOfTurn(Board* gameBoard, Player* &currPlayer, bool &endTurn, int numPlayers, int &currPos, bool &endGame)
{
  //std::cout << "called endTurn" << std::endl;
  std::vector<Player>* players = gameBoard->getPlayers();

  endTurn = true;

  for (int i = 0; i < 4; i++) {
    Card* noble = gameBoard->getCard(3,i);
    if (noble != nullptr) {
      int success = currPlayer->acquireNoble(noble);
      if (success == 1) {
        gameBoard->setNull(i);
        std::cout<< "Noble Acquired!" << std::endl;
        break;
      }
    }
  }

  endGame = endOfGame(currPlayer);

  if (!endGame) {
    //update whose turn it is
    currPos++;
    if (currPos == numPlayers) {
      currPos = 0;
    }
    currPlayer = &players->at(currPos);
  }
}

bool endOfGame(Player* currPlayer)
{

  std::string winner = currPlayer->getName();
  if (currPlayer->getPoints() >= 15) {
    std::cout << "Congratulations " << winner << "you have won by acquiring 15 points!" << std::endl;
    return true;
  }

  return false;
}

int main(int argc, char const *argv[]) {
  //int numPlayers = argv[0];
  int numPlayers = 2;
  Player* currPlayer;
  int currPos = 0;
  std::vector<std::string> names;
  std::string name = "playerOne";
  names.push_back(name);
  name = "BOT";
  names.push_back(name);
  Board* game = initializeGame(names);

  std::vector<Player>* players = game->getPlayers();
  currPlayer = &players->at(0);

  //getline variables
  int numCharsEntered = -5;
  size_t bufferSize = 0;		//how large allocated buffer is
  char *lineEntered = NULL;	//buffer holding user inputted string

  //gameControl Flag Variables
  bool endGame = false;
  bool endTurn = false;

  //while loop that starts the game/ keeps it going
  while (endGame == false)
  {
    showBoard(game);
    endTurn = false;
    //parse user input and run corresponding commands
    while (endTurn == false)
    {
      //get user input
      while(1)
      {
        //std::cout << "Player " << currPlayer->getName() << " it is your turn. "  << '\n';
        printf(": ");
        numCharsEntered = getline(&lineEntered, &bufferSize, stdin);
        if (numCharsEntered == -1)
          clearerr(stdin);
        else
          break;
      }

      char *token;
      //null terminate the user input
      lineEntered[numCharsEntered - 1] = '\0';

      token = strtok(lineEntered, " ");

      if (strcmp(token, "buy") == 0) {
        //get number of the card selected from the gameboard
        token = strtok(NULL, " ");
        int val;
        if (token == NULL) {
          std::cout << "Please indicate a card you wish to buy." << '\n';
        }
        else {
          if (strlen(token) > 1) {
            if ((char)token[1] == '0') {
              val = 10;
            }
            else {
              val = 11;
            }
          }
          else {
            char num = token[0];
            val = num - 48;
          }
          std::cout << "val is: " << val << '\n';
          //convert the number into the rows/columns as stored in board class
          if (val < 4) {
            buy(game, currPlayer, 2, val);
          }
          else if (val > 3 && val < 8) {
            int col = val % 4;
            buy(game, currPlayer, 1, col);
          }
          else
          {
            int col = val % 4;
            buy(game, currPlayer, 0, col);
          }
          endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
          std::cout << "It is the end of your turn." << '\n';
        }
      }

      else if (strcmp(token, "reserve") == 0) {
        //get number of the card selected from the gameboard
        token = strtok(NULL, " ");
        int val;
        if (token == NULL) {
          std::cout << "Please indicate a card you wish to reserve." << '\n';
        }
        else {
          if (strlen(token) > 1) {
            if ((char)token[1] == '0') {
              val = 10;
            }
            else {
              val = 11;
            }
          }
          else {
            char num = token[0];
            val = num - 48;
          }
          //convert the number into the rows/columns as stored in board class
          if (val < 4) {
            reserve(game, currPlayer, 2, val);
          }
          else if (val > 3 && val < 8) {
            int col = val % 4;
            reserve(game, currPlayer, 1, col);
          }
          else
          {
            int col = val % 4;
            reserve(game, currPlayer, 0, col);
          }

          endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
          std::cout << "It is the end of your turn." << '\n';
        }
      }

      else if (strcmp(token, "claim") == 0) {
        //get number of which card in the reserved cards vec will be claimed
        token = strtok(NULL, " ");
        int cardLocation;
        if (token == NULL) {
          std::cout << "Please indicate which reserved card you wish to claim." << '\n';
          break;
        }
        else {
          char num = token[0];
          cardLocation = num - 48;
        }

        //get which token will joker(yellow) count for
        token = strtok(NULL, " ");
        int tokenInc;
        if (token == NULL) {
          std::cout << "Please indicate which token the joker will count towards." << '\n';
          break;
        }
        else {
          char num = token[0];
          tokenInc = num - 48;
        }

        claim(currPlayer, cardLocation, tokenInc);
        endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
        std::cout << "It is the end of your turn." << '\n';
      }

      else if (strcmp(token, "grab") == 0) {
        int coins[5];

        for (int i = 0; i < 5; i++) {
          token = strtok(NULL, " ");
          if (token == NULL) {
            std::cout << "Please enter values for all 5 denominations when grabbing tokens." << '\n';
            break;
          }
          char num = token[0];
          int val = num - 48;
          if (val > 2) {
            std::cout << "You cannot grab more than 2 tokens." << '\n';
            break;
          }
          coins[i] = val;
        }

        int success = getTokens(game, currPlayer, coins);
        if (success == 1) {
          endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
          std::cout << "It is the end of your turn." << '\n';
        }
      }

      else if(strcmp(token, "add") == 0)
      {
        int coins[5];

        for (int i = 0; i < 5; i++) {
          token = strtok(NULL, " ");
          if (token == NULL) {
            std::cout << "Please enter values for all 5 denominations when grabbing tokens." << '\n';
            break;
          }
          char num = token[0];
          int val = num - 48;
          if (val > 7) {
            std::cout << "You can only add up to 7 tokens to your hand." << '\n';
            break;
          }
          coins[i] = val;
        }
        Add(game, currPlayer, coins);
      }

      else if(strcmp(token, "bonus") == 0)
      {
        int coins[5];

        for (int i = 0; i < 5; i++) {
          token = strtok(NULL, " ");
          if (token == NULL) {
            std::cout << "Please enter values for all 5 denominations when adding bonuses." << '\n';
            break;
          }
          char num = token[0];
          int val = num - 48;
          coins[i] = val;
        }
        AddBonus(game, currPlayer, coins);
      }

      else if (strcmp(token, "show") == 0) {
        show(currPlayer);
      }

      else if (strcmp(token, "board") == 0) {
        showBoard(game);
      }

      else if (strcmp(token, "supply") == 0) {
        showSupply(game);
      }

      else if (strcmp(token, "end") == 0) {
        endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
        std::cout << "You have ended your turn." << '\n';

      }
    }
  }

  cleanUp(game);
  return 0;
}
