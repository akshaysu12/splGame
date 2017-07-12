#include <vector>
#include <string>

#ifndef CARD_HPP
#define CARD_HPP

class Card
{
private:
  int level;
  int points;
  int cost[5];
  int resource[5];
  std::string resourceColor;

public:
  Card(int lvl, int pts, std::vector<int> cost, int* resource);

  // accessor functions
  int* getCost();       //return cost of card
  int getPoints();      //return prestige points
  int* getResource();   //accessor function to get resource of card
  std::string getColor();

};

#endif
