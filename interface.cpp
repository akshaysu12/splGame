#include "interface.hpp"
#include "playGame.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>


void playGame()
{
  std::vector<std::string> names;
  std::string name = "playerOne";
  names.push_back(name);
  name = "BOT";
  names.push_back(name);
  play(names);
}

/******** menu options *******
1. play game
2. simulate game -- To ADD
3. rulesf
4. exit
***************************/
int main ()
{

  /*
  std::cout << "|" << std::setw(37) << " " << "MENU" << std::setw(37) << " " << "|" << std::endl;
  std::cout << "1. Play Game" << '\n';
  //std::cout << "2. Simulate Game Between Two Bots." << '\n'; -- TO ADD
  std::cout << "2. Read the rules for Splendor" << '\n';
  std::cout << "3. Exit" << '\n';

  int choice = getchar();

  switch (choice) {
    case '1':
      playGame();
      break;

    case '2':
      //simGame();
      std::cout << "sim" << '\n';
      break;

    case '2':
      rules();
      break;
    case '3':
      std::cout << "Good-Bye!" << '\n';
      break;
  }
  */
  playGame();
  return 0;
}
