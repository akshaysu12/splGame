#include "playGame.hpp"
#include "draw.hpp"
#include "botPlayer.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**********\
Testing Functions
************/
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

//bypass rules and add as many permenants you want to your player - used for testing noble cards
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

/***************
Player Actions
***************/


/******** Help Functions *********/

/************
Function: help
Description: removes card from the gameboard and adds it to player
*************/

void help()
{
  makeGridLine();
  std::cout << "List of Commands: [words] are arguments required for the command (without the brackets)" << '\n';
  makeGridLine();
  std::cout << "rules                          Brings up the rules to the game." << '\n';
  std::cout << "help                           Brings up the help menu for commands." << '\n';
  std::cout << "buy [number]                   Purchase a card on the gameboard." << '\n';
  std::cout << "reserve [number]               Reserve a card (limit 3)" << '\n';
  std::cout << "grab [N N N N N]               Grab tokens from the supply to buy cards (must have a number for each color)."<< '\n';
  std::cout << "show                           Display your current tokens, bonuses, points and reserved cards." << '\n';
  std::cout << "players                        Display all players' current tokens, bonuses, points." << '\n';
  std::cout << "supply                         Display the current available supply of tokens." << '\n';
  std::cout << "board                          Display the gameboard." << '\n';
  std::cout << "end                            End your turn with no action." << '\n';
  std::cout << "resign                         End the game." << '\n';
  std::cout << "add                            Cheat function to manually grab as many tokens as you want." << '\n';
  std::cout << "bonus                          Cheat function to manually add as many bonuses as you want." << '\n';
  makeGridLine();

}

/************
Function: rules
Description: Creates a child process and then passes that to the OS to open rules.txt in vim
*************/

void rules()
{
  pid_t spawnpid = -5;
  int childExitMethod = -5;
  //create an argument to
  char* args[3];
  args[0] = (char*) "vim";
  args[1] = (char*) "rules.txt";
  args[2] = NULL;
  spawnpid = fork();
  switch(spawnpid)
  {
    case 0:
      if (execvp(args[0], args) < 0)
      {
        perror("exec failure!");
        exit(1);
      }

    default:
      //here we wait for the child process to complete because it is a foreground process
      spawnpid = waitpid(spawnpid, &childExitMethod, 0);
  }
}


/************
Function: buy
Description: removes card from the gameboard and adds it to player
*************/

int buy(Board* gameBoard, Player* currPlayer, int row, int column)
{
  Card* cardWanted = gameBoard->getCard(row, column);
  int success = currPlayer->buyCard(cardWanted);
  if (success == 1) {
    std::cout << "---------------------Card Successfully Bought!-------------------" << std::endl;
    int* cost = cardWanted->getCost();
    gameBoard->addTokens(cost);
    gameBoard->replaceCard(row, column);
    return 1;
  }
  else {
    std::cout << "Sorry, you are unable to purchase that card." << std::endl;
    return 0;
  }
}

int reserve(Board* gameBoard, Player* currPlayer, int row, int column)
{
  std::vector<Card*> *reserved = currPlayer->getReservedCards();
  if (reserved->size() >= 3) {
    std::cout << "You cannot reserve any more cards." << '\n';
    return -1;
  }

  currPlayer->reserveCard(gameBoard->getCard(row,column));
  gameBoard->replaceCard(row, column);
  gameBoard->decrementYellow();
  return 1;
}

void claim(Player* currPlayer, int cardLocation, int tokenReplace)
{
  currPlayer->buyReserveCard(cardLocation, tokenReplace);
}

void showSupply(Board* gameBoard)
{

  makeGridLine();

  //player name as header
  printHeadCell("Supply");
  int* supply = gameBoard->getSupply();
  std::string tokenString = "[" + std::to_string(supply[0]) + " " + std::to_string(supply[1]) + " " + std::to_string(supply[2]) + " " + std::to_string(supply[3]) + " " + std::to_string(supply[4]) + "]";
  printBodyCell(tokenString);
  std::cout << std::endl;
  makeGridLine();
  /*
  old deprecated display code
  for (int i = 0; i < 5; i++) {
    std::cout << supply[i] << " ";
  }
  std::cout << std::endl;
  */
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
        return 0;
      }
      DBLcount++;
    }
    if (DBLcount > 1) {
      std::cout << "Sorry. You can only grab one type of color if you are grabbing two tokens." << std::endl;
      return 0;
    }

    if (toGrab[i] > 0) {
      SGLcount++;
    }
    if (SGLcount > 3) {
      std::cout << "Sorry. You can only grab 3 tokens if you are grabbing multiple colors." << std::endl;
      return 0;
    }
  }

  gameBoard->removeTokens(toGrab);
  currPlayer->addTokens(toGrab);

  std::cout << std::endl;
  makeGridLine();
  std::cout << "|             " << "You have grabbed: ";
  for (int i = 0; i < 5; i++) {
      std::cout << toGrab[i] << ":" << colors[i] << " ";
  }
  std::cout << "tokens           |" << std::endl;
  makeGridLine();
  std::cout << std::endl;
  return 1;
}

void show(Player* currPlayer)
{
  makeGridLine();

  //player name as header
  printHeadCell(currPlayer->getName());

  //Points
  printBodyCell("Points:" + std::to_string(currPlayer->getPoints()));

  //Tokens
  int* tokens = currPlayer->getTokens();
  std::string tokenString = "Tokens: [";
  tokenString = tokenString + std::to_string(tokens[0]) + " " + std::to_string(tokens[1]) + " " + std::to_string(tokens[2]) + " " + std::to_string(tokens[3]) + " " + std::to_string(tokens[4]) + "]";
  printBodyCell(tokenString);

  //Resources
  int* resources = currPlayer->showResources();
  std::string resourceString = "Resources: [";
  resourceString = resourceString + std::to_string(resources[0]) + " " + std::to_string(resources[1]) + " " + std::to_string(resources[2]) + " " + std::to_string(resources[3]) + " " + std::to_string(resources[4]) + "]";
  printBodyCell(resourceString);

  std::cout << '\n';

  //ReservedCards
  std::vector<Card*> *reserved = currPlayer->getReservedCards();
  if (reserved->size() != 0) {
   makeGridLine();
  }

  for (int i = 0; i < reserved->size(); i++) {
    printHeadCell("Reserved Card " + std::to_string(i) + ":");

    //card point values
    //std::cout << "Points:" + currPlayer->getPoints() << '\n';
    printBodyCell("Points:" + std::to_string(reserved->at(i)->getPoints()));


    //card cost
    int *cost = reserved->at(i)->getCost();
    std::string costString = "Cost: [";
    costString = costString + std::to_string(cost[0]) + " " + std::to_string(cost[1]) + " " + std::to_string(cost[2]) + " " + std::to_string(cost[3]) + " " + std::to_string(cost[4]) + "]";
    printBodyCell(costString);
    std::cout << '\n';
    if (i == reserved->size()) {
      makeGridLine();
    }
  }

  makeGridLine();
  std::cout << std::endl;
}

void showAll(Board* gameBoard, std::vector<Player> *players)
{
  for (int i = 0; i < players->size(); i++) {
    Player currPlayer = players->at(i);
    makeGridLine();

    //player name as header
    printHeadCell(currPlayer.getName());

    //Points
    printBodyCell("Points:" + std::to_string(currPlayer.getPoints()));

    //Tokens
    int* tokens = currPlayer.getTokens();
    std::string tokenString = "Tokens: [";
    tokenString = tokenString + std::to_string(tokens[0]) + " " + std::to_string(tokens[1]) + " " + std::to_string(tokens[2]) + " " + std::to_string(tokens[3]) + " " + std::to_string(tokens[4]) + "]";
    printBodyCell(tokenString);

    //Resources
    int* resources = currPlayer.showResources();
    std::string resourceString = "Resources: [";
    resourceString = resourceString + std::to_string(resources[0]) + " " + std::to_string(resources[1]) + " " + std::to_string(resources[2]) + " " + std::to_string(resources[3]) + " " + std::to_string(resources[4]) + "]";
    printBodyCell(resourceString);

    std::cout << '\n';
    makeGridLine();
  }

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

void resign(Board* gameBoard, Player* &currPlayer, bool &endTurn, int numPlayers, int &currPos, bool &endGame) {

  //update the player to get the name for the victor
  std::vector<Player>* players = gameBoard->getPlayers();

  currPos++;
  if (currPos == numPlayers) {
    currPos = 0;
  }
  currPlayer = &players->at(currPos);
  std::string winner = currPlayer->getName();
  std::cout << "Congratulations " << winner << " you have won by resignation!" << std::endl;
  endTurn = true;
  endGame = true;
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

void play(std::vector<std::string> names) {
  int numPlayers = 2;
  Player* currPlayer;
  int currPos = 0;
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

    //skip getting input if the current player is a bot
    if (currPlayer->getBotStatus()) {
      botTurn(game, currPlayer);
      endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
      continue;
    }

    int first = 1;

    //parse user input and run corresponding commands
    while (endTurn == false)
    {
      //get user input
      while(1)
      {
        fflush(stdin);
        if (first == 1) {
          std::cout << currPlayer->getName() << " it is your turn. "  << '\n';
          std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
          std::cin.ignore();
        }
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
            if(buy(game, currPlayer, 2, val))
            {
              endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
              std::cout << "------------------------------ It Is The End Of Your Turn ----------------------------" << '\n';
              std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
              std::cin.ignore();
              std::cout << std::endl;
              std::cout << std::endl;
              std::cout << std::endl;
              std::cout << std::endl;
            }
          }
          else if (val > 3 && val < 8) {
            int col = val % 4;
            if(buy(game, currPlayer, 1, col))
            {
              endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
              std::cout << "------------------------------ It Is The End Of Your Turn ----------------------------" << '\n';
              std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
              std::cin.ignore();
              std::cout << std::endl;
              std::cout << std::endl;
              std::cout << std::endl;
              std::cout << std::endl;
            }
          }
          else
          {
            int col = val % 4;
            if(buy(game, currPlayer, 0, col))
            {
              endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
              std::cout << "------------------------------ It Is The End Of Your Turn ----------------------------" << '\n';
              std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
              std::cin.ignore();
              std::cout << std::endl;
              std::cout << std::endl;
              std::cout << std::endl;
              std::cout << std::endl;
            }
          }
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
          int success;
          if (val < 4) {
            success = reserve(game, currPlayer, 2, val);
          }
          else if (val > 3 && val < 8) {
            int col = val % 4;
            success = reserve(game, currPlayer, 1, col);
          }
          else
          {
            int col = val % 4;
            success = reserve(game, currPlayer, 0, col);
          }
          if (success == 1) {
            endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
            std::cout << "------------------------------ It Is The End Of Your Turn ----------------------------" << '\n';
            std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
            std::cin.ignore();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
          }
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

        //int success = getTokens(game, currPlayer, coins)
        if(getTokens(game, currPlayer, coins))
        {
          endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
          std::cout << "------------------------------ It Is The End Of Your Turn ----------------------------" << '\n';
          std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
          std::cin.ignore();
          std::cout << std::endl;
          std::cout << std::endl;
          std::cout << std::endl;
          std::cout << std::endl;
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

      else if (strcmp(token, "players") == 0) {
        showAll(game, game->getPlayers());
      }

      else if (strcmp(token, "board") == 0) {
        showBoard(game);
      }

      else if (strcmp(token, "supply") == 0) {
        showSupply(game);
      }

      else if (strcmp(token, "help") == 0) {
        help();
      }

      else if(strcmp(token, "rules") == 0)
      {
        rules();
      }

      else if(strcmp(token, "resign") == 0)
      {
        resign(game, currPlayer, endTurn, numPlayers, currPos, endGame);
      }

      else if (strcmp(token, "end") == 0) {
        endOfTurn(game, currPlayer, endTurn, numPlayers, currPos, endGame);
        std::cout << "------------------------------ You Have Ended Your Turn ------------------------------" << '\n';
        std::cout << "------------------------------ Press [Enter] to Continue -----------------------------";
        std::cin.ignore();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
      }

      //make sure player greeting does not get re-shown
      first = 0;
    }
  }

  cleanUp(game);
}
