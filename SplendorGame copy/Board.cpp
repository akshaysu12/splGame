#include "Board.hpp"
#include <vector>
#include <iostream>

Board::Board(std::vector<Player> *players)
{
  //initialize tokens
  for (int i = 0; i < 5; i++) {
    tokens[i] = 7;
  }

  //initialize players
  this->players = players;

  //initialize strings for colors
  colors[0] = "White";
  colors[1] = "Black";
  colors[2] = "Red";
  colors[3] = "Blue";
  colors[4] = "Green";

  for (int i = 0; i < 4; i++) {
    std::vector<Card* > cardRow;
    boardCards.push_back(cardRow);
  }

}

//mutator functions
void Board::createCardSupply(std::vector<Card> *levelOneCards, std::vector<Card> *levelTwoCards, std::vector<Card> *levelThreeCards, std::vector<Card> *nobleCards)
{
  this->levelOneCards = levelOneCards;
  this->levelTwoCards = levelTwoCards;
  this->levelThreeCards = levelThreeCards;
  this->nobleCards = nobleCards;
}

void Board::createGameBoard()
{
  int count = 0;
  for (int i = 0; i < 4; i++) {
      Card* cardPtr = &levelOneCards->at(i);
      boardCards[count].push_back(cardPtr);
    }

  count++;
  for (int i = 0; i < 4; i++) {
      Card* cardPtr = &levelTwoCards->at(i);
      boardCards[count].push_back(cardPtr);
    }

  count++;
  for (int i = 0; i < 4; i++) {
      Card* cardPtr = &levelThreeCards->at(i);
      boardCards[count].push_back(cardPtr);
    }

  count++;
  for (int i = 0; i < 4; i++) {
      Card* cardPtr = &nobleCards->at(i);
      boardCards[count].push_back(cardPtr);
    }

  lvlOneDeck = 4;
  lvlTwoDeck = 4;
  lvlThreeDeck = 4;

}

void Board::replaceCard(int row, int column)
{
  if (row == 0) {
    if (lvlOneDeck == 40) {
      boardCards[row][column] = nullptr;
    }
    else
      boardCards[row][column] = &levelOneCards->at(lvlOneDeck);
      lvlOneDeck++;
  }

  else if (row == 1) {
    if (lvlTwoDeck == 30) {
      boardCards[row][column] = nullptr;
    }
    else
      boardCards[row][column] = &levelTwoCards->at(lvlTwoDeck);
      lvlTwoDeck++;
  }

  else {
    if (lvlThreeDeck == 30) {
      boardCards[row][column] = nullptr;
    }
    else
      boardCards[row][column] = &levelThreeCards->at(lvlThreeDeck);
      lvlThreeDeck++;
  }

}

void Board::setNull(int column)
{
  boardCards[3][column] = nullptr;
}

void Board::removeTokens(int* toRemove)
{
  for (int i = 0; i < 5; i++) {
    tokens[i] = tokens[i] - toRemove[i];
  }
}
void Board::addTokens(int* toAdd)
{
  for (int i = 0; i < 5; i++) {
    tokens[i] = tokens[i] + toAdd[i];
  }
}

//reduce number of yellow tokens available
void Board::decrementYellow()
{
  tokens[5]--;
}

void Board::cleanUp()
{
  //deallocate memory for cards
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

  for (int i = 0; i < players->size(); i++) {
    players->pop_back();
  }
}


//accessor functions
Card* Board::getCard(int row, int column)
{
  return boardCards[row][column];
}

std::vector<Player>* Board::getPlayers()
{
  return players;
}

int* Board::getSupply()
{
  int *supply = tokens;
  return supply;
}

std::string* Board::getColors()
{
  std::string *tokenColors = colors;
  return tokenColors;
}
