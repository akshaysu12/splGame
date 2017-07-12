#include <vector>
#include "Player.hpp"
#include <iostream>

//Constructor
Player::Player(std::string name)
{
  //initialize resources/pts to 0
  points = 0;
  for (int i = 0; i < 5; i++) {
    bonuses[i] = 0;
    tokens[i] = 0;
  }
  this->name = name;
}

/***************
Accessor Functions
****************/

int* Player::getTokens()
{
  int* tokenptr = tokens;
  return tokenptr;
}

int* Player::showResources()
{
  int* resourcePtr = bonuses;
  return resourcePtr;
}

std::vector<Card*>* Player::getReservedCards()
{
  std::vector<Card*>* reserved = &reservedCards;
  return reserved;
}

int Player::getPoints()
{
  return points;
}
std::string Player::getName()
{
  return name;
}

/***********************************
Actions a Player can take on their turn
***********************************/

//add tokens from supply to player's reserves
void Player::addTokens(int tokensRetrieved[])
{
  for (int i = 0; i < 5; i++) {
    tokens[i] = tokens[i] + tokensRetrieved[i];
  }
}

//bypass rules to directly add bonusus - testing function
void Player::addBonus(int toAdd[])
{
  for (int i = 0; i < 5; i++) {
    bonuses[i] = bonuses[i] + toAdd[i];
  }
}


//return 1 if succesful, -1 if not
int Player::buyCard(Card* boughtCard)
{
  int *costs = boughtCard->getCost();

  for (int i = 0; i < 5; i++) {
    //check that the sum of resources for the player is enough to buy the card
    if (bonuses[i] + tokens[i] < costs[i]) {
      return -1;
    }
  }

  for (int i = 0; i < 5; i++) {
    //check if all tokens need to be used - usually this is the case (tokens + bonuses needed to buy cards)
    if (costs[i] > tokens[i]) {
      this->tokens[i] = 0;
    }
    //conditional if only tokens need to be used to purchase card
    else {
      this->tokens[i] = this->tokens[i] - costs[i];
    }
  }

  //getResource returns an array where only one of the values is not 0. This is the permenant resource of the card
  int *resource = boughtCard->getResource();

  for (int i = 0; i < 5; i++) {
    if (resource[i] != 0) {
      bonuses[i]++;
    }
  }

  //add cards points to player's point total
  points = points + boughtCard->getPoints();

  return 1;
}

//cardLocation - position in reservedCards vector
//tokenReplace - position in tokens Array that the yellow token will replace
int Player::buyReserveCard(int cardLocation, int tokenReplace)
{
  tokens[tokenReplace]++;   //increment tokenCount of color yellow will replace
  tokens[5]--;              //decrement number of yellow tokens

  int success = buyCard(reservedCards[cardLocation]);

  //if player able to buy the card
  if (success == 1) {
    reservedCards.erase(reservedCards.begin()+cardLocation);
    return 1;
  }

  //if player unable to buy the card - reset token counts
  else {
    tokens[tokenReplace]--;
    tokens[5]++;
    return -1;
  }
}

void Player::reserveCard(Card* cardToReserve)
{
  reservedCards.push_back(cardToReserve);
  tokens[5]++;
}

//called by endTurn action
int Player::acquireNoble(Card* noble)
{
  int *cost = noble->getCost();
  for (int i = 0; i < 5; i++) {
    if ((int)bonuses[i] - (int)cost[i] < 0) {
      return -1;
    }
  }

  //consider keeping track of nobles acquired. for now just adds to points
  points = points + noble->getPoints();
  return 1;
}
