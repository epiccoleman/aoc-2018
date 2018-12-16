#include "MinecartMadness.h"

#include <algorithm>
#include <set>
#include <iostream>
#include <utility>

void MinecartMadness::Cart::advance() {
//  std::cout << "advancing cart at " << location.x << ',' << location.y << std::endl;
  // if()
  location += direction;
//  std::cout << "advanced to" << location.x << ',' << location.y << std::endl;

////  std::cout << "looking at : (" << location.x << ',' << location.y << ')' << std::endl;
  char road_type = board[location.y][location.x];
  switch (road_type){
  case '/':
////    std::cout << "got forward slash" << std::endl;
    handle_forward_slash();
    break;
  case '\\':
    handle_back_slash();
    break;
  case '+':
    handle_crossroads();
    break;
  // default:
//   std::cout << "got something else: '" << road_type << '\'' <<  std::endl;
  }
}

void MinecartMadness::Cart::handle_forward_slash() {
  if( direction == LEFT ){
    direction = DOWN;
  }
  else if ( direction == DOWN ) {
    direction = LEFT;
  }
  else if ( direction == UP ) {
    direction = RIGHT;
  }
  else if ( direction == RIGHT ) {
    direction = UP;
  }
}

void MinecartMadness::Cart::handle_back_slash() {
  if( direction == LEFT ){
    direction = UP;
  }
  else if ( direction == DOWN ) {
    direction = RIGHT;
  }
  else if ( direction == UP ) {
    direction = LEFT;
  }
  else if ( direction == RIGHT ) {
    direction = DOWN;
  }
}

void MinecartMadness::Cart::handle_crossroads() {
  switch(next_crossroad_dir){
  case 0:
    turn_left();
    break;
  case 1:
    break;
  case 2:
    turn_right();
    break;
  }
  next_crossroad_dir++;
  next_crossroad_dir %= 3;
}

void MinecartMadness::Cart::turn_left() {
  if( direction == LEFT ){
    direction = DOWN;
  }
  else if ( direction == DOWN ) {
    direction = RIGHT;
  }
  else if ( direction == UP ) {
    direction = LEFT;
  }
  else if ( direction == RIGHT ) {
    direction = UP;
  }
}

void MinecartMadness::Cart::turn_right() {
  if( direction == LEFT ){
    direction = UP;
  }
  else if ( direction == DOWN ) {
    direction = LEFT;
  }
  else if ( direction == UP ) {
    direction = RIGHT;
  }
  else if ( direction == RIGHT ) {
    direction = DOWN;
  }
}

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
          carts.push_back(Cart(j, i, LEFT, board));
          break;
        case '>':
          carts.push_back(Cart(j, i, RIGHT, board));
          break;
        case '^':
          carts.push_back(Cart(j, i, UP, board));
          break;
        case 'v':
          carts.push_back(Cart(j, i, DOWN, board));
          break;
        }
      }
  }
}

void MinecartMadness::MinecartSimulation::simulate() {
    for (auto &cart : carts) {
        cart.advance();
    }
}

std::pair<int, int> MinecartMadness::MinecartSimulation::find_first_crash(){
  int max_iterations = 1000000;
  for(int i = 0; i < max_iterations; i++){

    std::set<std::pair<int, int> > occupied_locations;

    for (const auto &cart : carts) {
      if (! occupied_locations.insert(std::make_pair(cart.location.x, cart.location.y)).second){
        return std::make_pair(cart.location.x, cart.location.y);
      }
    }
    simulate();
  }
  return std::pair<int,int> { -1, -1 };
}



