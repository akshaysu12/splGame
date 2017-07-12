#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include "Card.hpp"

class Player
{
private:
  int points;       //number of prestige points player has
  std::string name;

  //white, black, red, blue, green
  int bonuses[5]; //number of permenant resources bought through development Cards

  //white, black, red, blue, green, yellow
  int tokens[6];  //number of temporary tokens player has to buy development cards

  std::vector<Card*> reservedCards; //max 3 - pointers to cards reserved with yelow tokens
public:
  //constructor
  Player(std::string name);

  //accessor functions
  int* showResources();
  std::vector<Card*>* getReservedCards();
  int getPoints();
  std::string getName();
  int* getTokens();


/***********************************
Actions a Player can take on their turn
***********************************/

  int buyCard(Card* boughtCard);
  int buyReserveCard(int cardLocation, int tokenReplace);
  void addTokens(int tokensRetrieved[]);
  void addBonus(int toAdd[]);
  void reserveCard(Card* cardToReserve);
  void endTurn();
  int acquireNoble(Card* noble);
};

#endif
