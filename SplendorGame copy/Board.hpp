#ifndef BOARD_HPP
#define BOARD_HPP

#include "Player.hpp"
#include <vector>
#include <string>

class Board
{
private:
  //current cards on the board
  std::vector<std::vector<Card*> > boardCards;

  //stores of cards
  std::vector<Card> *levelOneCards;
  std::vector<Card> *levelTwoCards;
  std::vector<Card> *levelThreeCards;
  std::vector<Card> *nobleCards;

  //which card in each deck
  int lvlOneDeck;
  int lvlTwoDeck;
  int lvlThreeDeck;

  //array of players in the game
  std::vector<Player> *players;
  int numPlayers;   // max num of players
  int tokens[6];    // current supply of tokens available to players
  std::string colors[5];

public:

  Board(std::vector<Player> *players);

  //mutator functions
  void replaceCard(int row, int column);
  void removeTokens(int* toRemove);
  void addTokens(int* toAdd);
  void decrementYellow();
  void createCardSupply(std::vector<Card> *levelOneCards, std::vector<Card> *levelTwoCards, std::vector<Card> *levelThreeCards, std::vector<Card> *nobleCards);
  void createGameBoard();
  void cleanUp();
  void setNull(int column);

  //accessor functions
  Card* getCard(int row, int column);
  std::vector<Player>* getPlayers();
  int* getSupply();
  std:: string* getColors();
};

#endif
