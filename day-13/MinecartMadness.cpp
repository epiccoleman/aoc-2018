#include "MinecartMadness.h"
#include <algorithm>

MinecartMadness::MinecartSimulation::MinecartSimulation(std::vector<std::string> gameboard)
  : board(gameboard)
{
  find_carts();
}

void MinecartMadness::MinecartSimulation::find_carts() {

  for (int i = 0; i < board.size(); i++) { 
    for (int j = 0; j < board[i].size(); j++) { 
      char c = board[i][j];
        switch(c) {
        case '<':
          carts.push_back(Cart(i, j, LEFT));
          break;
        case '>':
          carts.push_back(Cart(i, j, RIGHT));
          break;
        case '^':
          carts.push_back(Cart(i, j, UP));
          break;
        case 'v':
          carts.push_back(Cart(i, j, DOWN));
          break;
        }
      }
  }
}

