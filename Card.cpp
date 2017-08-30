#include "Card.hpp"
#include <vector>

Card::Card(int level, int points, std::vector<int> cost, int* resource)
{
  this->level = level;
  this->points = points;
  for (int i = 0; i < 5; i++) {
    this->cost[i] = cost[i];
    this->resource[i] = resource[i];
    if (resource[i] != 0) {
      if (i == 0) {
        resourceColor = "White";
      }
      else if (i == 1) {
        resourceColor = "Black";
      }
      else if (i == 1) {
        resourceColor = "Red";
      }
      else if (i == 1) {
        resourceColor = "Blue";
      }
      else {
        resourceColor = "Green";
      }
    }
  }
}

//accessor function to return cost of card
int* Card::getCost()
{
  int* cardCosts = cost;
  return cardCosts;
}

//accessor function to return prestige points
int Card::getPoints()
{
  return points;
}

//accessor function to return resources of card
int* Card::getResource()
{
  int* cardResources = resource;
  return cardResources;
}

std::string Card::getColor()
{
  return resourceColor;
}
