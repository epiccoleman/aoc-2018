#include "MinecartMadness.h"

#include <algorithm>
#include <set>
#include <iostream>
#include <utility>

void MinecartMadness::Cart::advance(char road_type) {
  location += direction;
  switch (road_type){
  case '/':
    handle_forward_slash();
    break;
  case '\\':
    handle_back_slash();
    break;
  case '+':
    handle_crossroads();
    break;
  }
}

MinecartMadness::Cart::Cart(int loc_x, int loc_y, utils::Point initial_dir)
  : next_crossroad_dir(0),
    location { loc_x, loc_y },
    direction (initial_dir),
    crashed(false)
{}

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

void MinecartMadness::Cart::mark_for_deletion() {
  crashed = true;
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

utils::Point MinecartMadness::Cart::next_location() {
  return location + direction;
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
          carts.push_back(Cart(j, i, LEFT));
          break;
        case '>':
          carts.push_back(Cart(j, i, RIGHT));
          break;
        case '^':
          carts.push_back(Cart(j, i, UP));
          break;
        case 'v':
          carts.push_back(Cart(j, i, DOWN));
          break;
        }
      }
  }
}

bool MinecartMadness::MinecartSimulation::crash_at(utils::Point loc) {
  auto crash = std::find_if(carts.begin(), carts.end(), [loc](MinecartMadness::Cart cart){
      return !cart.crashed && loc.x == cart.location.x  && loc.y == cart.location.y;
    });
  return crash != carts.end();
}

void MinecartMadness::MinecartSimulation::mark_carts_at_loc_for_deletion(utils::Point loc) {
  for (auto &cart : carts) {
    if (cart.location == loc){
      cart.mark_for_deletion();
    }
  }
}

void MinecartMadness::MinecartSimulation::remove_marked_carts() {
  carts.erase(
              std::remove_if(carts.begin(), carts.end(),
                             [](MinecartMadness::Cart cart){
                               return cart.crashed; } ),
              carts.end());
}

void MinecartMadness::MinecartSimulation::log_crash(utils::Point loc) {
  crashes.push_back(loc);
}

void MinecartMadness::MinecartSimulation::sort_carts(){
  std::sort(carts.begin(),
            carts.end(),
            [](MinecartMadness::Cart a, MinecartMadness::Cart b){
              if (a.location.y < b.location.y) return true;
              if (a.location.y == b.location.y && a.location.x < b.location.x) return true;
              return false;
            });
}

void MinecartMadness::MinecartSimulation::simulate() {
  sort_carts();
    for (auto &cart : carts) {
      auto next = cart.next_location();
      char road = board[next.y][next.x];

      if (crash_at(next)){
        log_crash(next);
        cart.advance(road);
        mark_carts_at_loc_for_deletion(next);
      }
      else {
        cart.advance(road);
      }
    }
    remove_marked_carts();
}

utils::Point MinecartMadness::MinecartSimulation::find_first_crash(){

  int max = 1000000;
  int i = 0;
  while(crashes.size() < 1 && i < max){
    simulate();
    i++;
  }

  return crashes.front();
}

utils::Point MinecartMadness::MinecartSimulation::find_last_cart(){

  int max = 1000000;
  int i = 0;
  while(carts.size() > 1 && i < max){
    simulate();
    i++;
  }

  return carts.front().location;
}
