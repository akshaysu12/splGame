#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "initGame.hpp"

int myrandom (int i) { return std::rand()%i;}

void shift(std::vector<int> &costs, int* resource, int i)
{
  int temp = costs[0];
  for (int j = 0; j < 4; j++)
  {
    costs[j] = costs[j+1];
    if (j == i) {
      resource[j] = 1;
    }
    else
      resource[j] = 0;
  }
  costs[4] = temp;
  if (i == 4) {
    resource[4] = 1;
  }
  else
    resource[4] = 0;
}

void generateSet(int costs[], std::vector<Card> *levelOneCards, int level, int points)
{
  int resource[5];
  std::vector<int> costVec (costs, costs + sizeof(resource)/sizeof(int));
  std::random_shuffle(costVec.begin(), costVec.end(), myrandom);
  Card *newCard = new Card(level, points, costVec, resource);
  levelOneCards->push_back(*newCard);
  for (int i = 0; i < 4; i++) {
    shift(costVec, resource, i);
    newCard = new Card(level, points, costVec, resource);
    levelOneCards->push_back(*newCard);
  }
}

void printCost(Card curr)
{
  int* toPrint = curr.getCost();
  for (int i = 0; i < 5; i++) {
    std::cout <<  toPrint[i]  << " ";
  }
  std::cout << '\n';
}

std::vector<Card>* generateLevelOneCards()
{
  std::vector<Card> *levelOneCards = new std::vector<Card>;
  int costs[5];

  //generate first set of level 1 cards. sum = 4 -> 4:1, 1:0
  for (int i = 0; i < 4; i++) {
    costs[i] = 1;
  }
  costs[4] = 0;
  generateSet(costs, levelOneCards, 1, 0);

  //generate second set of level 1 cards. sum = 5 -> 1:2, 3:1, 1:0
  costs[0]++;
  generateSet(costs, levelOneCards, 1, 0);

  //generate third set of level 1 cards - 2 2 1 0 0
  costs[1]++;
  costs[3]--;
  generateSet(costs, levelOneCards, 1, 0);

  //generate fourth set of level 1 cards - 3 1 1 0 0
  costs[0]++;
  costs[1]--;
  generateSet(costs, levelOneCards, 1, 0);

  //generate fifth set of level 1 cards -  2 1 0 0 0
  costs[0] = 2;
  costs[1] = 1;
  costs[2] = 0;
  generateSet(costs, levelOneCards, 1, 0);

  //generate sixth set of level 1 cards - 2 2 0 0 0
  costs[1]++;
  generateSet(costs, levelOneCards, 1, 0);

  //generate seventh set of level 1 cards - 3 0 0 0 0
  costs[0]++;
  costs[1] = 0;
  generateSet(costs, levelOneCards, 1, 0);

  //generate eigth set of level 1 cards -  4 0 0 0 0
  costs[0]++;
  generateSet(costs, levelOneCards, 1, 1);

  return levelOneCards;
}

std::vector<Card>* generateLevelTwoCards()
{
  std::vector<Card> *levelTwoCards = new std::vector<Card>;

  //generate first set of level two cards - 3 2 2 0 0
  int costs[5];
  costs[0] = 3;
  costs[1] = 2;
  costs[2] = 2;
  costs[3] = 0;
  costs[4] = 0;
  generateSet(costs, levelTwoCards, 2, 1);

  //generate second set of level two cards - 3 3 2 0 0
  costs[1]++;
  generateSet(costs, levelTwoCards, 2, 1);

  //generate third set of level two cards - 4 1 2 0 0
  costs[0]++;
  costs[1] = 1;
  generateSet(costs, levelTwoCards, 2, 2);

  //generate fourth set of level two cards - 5 3 0 0 0
  costs[0]++;
  costs[1] = 3;
  costs[2] = 0;
  generateSet(costs, levelTwoCards, 2, 2);

  //generate fifth set of level two cards - 5 0 0 0 0
  costs[1] = 0;
  generateSet(costs, levelTwoCards, 2, 2);

  //generate sixth set of level two cards - 6 0 0 0 0
  costs[0]++;
  generateSet(costs, levelTwoCards, 2, 3);

  return levelTwoCards;
}


std::vector<Card>*  generateLevelThreeCards()
{
  std::vector<Card> *levelThreeCards = new std::vector<Card>;

  //generate first set of level three cards - 5 3 3 3 0
  int costs[5];
  costs[0] = 5;
  costs[1] = 3;
  costs[2] = 3;
  costs[3] = 3;
  costs[4] = 0;
  generateSet(costs, levelThreeCards, 3, 3);

  //generate second set of level three cards - 6 3 3 0 0
  costs[0]++;
  costs[3] = 0;
  generateSet(costs, levelThreeCards, 3, 4);

  //generate third set of level three cards - 7 3 0 0 0
  costs[0]++;
  costs[2] = 0;
  generateSet(costs, levelThreeCards, 3, 4);

  //generate fourth set of level three cards - 7 0 0 0 0
  costs[1] = 0;
  generateSet(costs, levelThreeCards, 3, 5);

  return levelThreeCards;
}

std::vector<Card>* generateNobleCards()
{
  std::vector<Card> *nobleCards = new std::vector<Card>;

  //generate first set of level three cards - 3 3 3 0 0
  int costs[5];
  costs[0] = 3;
  costs[1] = 3;
  costs[2] = 3;
  costs[3] = 0;
  costs[4] = 0;
  generateSet(costs, nobleCards, 0, 3);

  //generate second set of level three cards - 4 4 0 0 0
  costs[0]++;
  costs[1]++;
  costs[2] = 0;
  generateSet(costs, nobleCards, 0, 3);

  return nobleCards;
}


Board* initializeGame(std::vector<std::string> names)
{
  srand(time(NULL));

  //create a vector of Players on the heap to initialize Board class with
  std::vector<Player> *players = new std::vector<Player>;

  //for now workaround - manually assign second player as a bot
  for (int i = 0; i < names.size(); i++) {
    Player *currPlayer;
    if (i == names.size()-1) {
      currPlayer = new Player(names[i], true);
    }
    else
      currPlayer = new Player(names[i], false);
    players->push_back(*currPlayer);
  }

  Board* game = new Board(players);

  std::vector<Card> *levelOneCards = generateLevelOneCards();
  std::vector<Card> *levelTwoCards = generateLevelTwoCards();
  std::vector<Card> *levelThreeCards = generateLevelThreeCards();
  std::vector<Card> *nobleCards = generateNobleCards();

  std::random_shuffle(levelOneCards->begin(), levelOneCards->end(), myrandom);
  std::random_shuffle(levelTwoCards->begin(), levelTwoCards->end(), myrandom);
  std::random_shuffle(levelThreeCards->begin(), levelThreeCards->end(), myrandom);
  std::random_shuffle(nobleCards->begin(), nobleCards->end(), myrandom);

  game->createCardSupply(levelOneCards, levelTwoCards, levelThreeCards, nobleCards);
  game->createGameBoard();
  return game;
}

void cleanUp(Board *gameboard)
{
  //deallocates cards and players
  gameboard->cleanUp();

  //deallocate remaining memory in gameboard
  delete gameboard;
}
