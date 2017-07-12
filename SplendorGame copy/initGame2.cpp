#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include "initGame.hpp"


void shift(std::vector<int> costs, int* resource, int i)
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

void generateSet(int costs[], std::vector<Card* > &levelOneCards)
{
  int resource[5];
  std::vector<int> v (costs, costs + sizeof(costs)/sizeof(int))
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  for (int i = 0; i < 4; i++) {
    shift(costs, resource, i);
    Card* newCard = new Card(0, 0, costs, resource);
    levelOneCards.push_back(newCard);
  }
}

std::vector<Card* > generateLevelOneCard()
{
  std::vector<Card* > levelOneCards;
  int costs[5];
  generateSet


/*
  //generate first set of level 1 cards. sum = 4 -> 4:1, 1:0
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == j) {
        costs[j] = 0;
        resource[j] = 1;
      }
      else{
        costs[j] = 1;
        resource[j] = 0;
      }
    }
    Card* newCard = new Card(0, 0, costs, resource);

  }

  //generate second set of level 1 cards. sum = 5 -> 1:2, 3:1, 1:0
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == j) {
        costs[j] = 0;
        resource[j] = 1;
      }
      else if (j = i + 1) {
        costs[j] = 2
        resource[j] = 0;
      }
      else if (j == 0 && i == 4)
      {
        costs[j] = 2;
        resource[j] = 0;
      }
      else{
        costs[j] = 1;
        resource[j] = 0;
      }
    }
    Card* newCard = new Card(0, 0, costs, resource);
  }

  //generate third set of level 1 cards. sum = 5 -> 2:2, 1:1, 2:0
  costs[0] = 2;
  costs[1] = 1;
  costs[2] = 0;
  costs[3] = 2;
  costs[4] = 0;
  int count = 0;
  while (count < 5) {
    int used[i];

  }
*/

}
/*
std::vector<Card*>  generateLevelTwoCard()
{

}

std::vector<Card*>  generateLevelThreeCard()
{

}

std::vector<Card*>  generateNobleCards()
{

}

void initializeGame(int numPlayers)
{

}

void cleanUp(Board* gameboard)
{

}
*/

/*
int main()
{
  srand(time(NULL));
  std::vector<Card> *levelOneCards = generateLevelOneCards();
  std::vector<Card> *levelTwoCards = generateLevelTwoCards();
  std::vector<Card> *levelThreeCards = generateLevelThreeCards();
  std::vector<Card> *nobleCards = generateNobleCards();

  std::random_shuffle(levelOneCards->begin(), levelOneCards->end(), myrandom);
  std::random_shuffle(levelTwoCards->begin(), levelTwoCards->end(), myrandom);
  std::random_shuffle(levelThreeCards->begin(), levelThreeCards->end(), myrandom);
  std::random_shuffle(nobleCards->begin(), nobleCards->end(), myrandom);


  for (int i = 0; i < levelOneCards->size(); i++) {
    printCost(levelOneCards->at(i));
  }


  Card *randCard = &levelOneCards->at(10);
  printCost(*randCard);

  for (int i = 0; i < levelOneCards->size(); i++) {
    levelOneCards->pop_back();
  }

  for (int i = 0; i < levelTwoCards->size(); i++) {
    levelTwoCards->pop_back();
  }

  for (int i = 0; i < levelThreeCards->size(); i++) {
    levelThreeCards->pop_back();
  }

  for (int i = 0; i < nobleCards->size(); i++) {
    nobleCards->pop_back();
  }

  return 0;
}
*/
