#include "MarbleMania.h"
#include <iostream>
#include <algorithm>

MarbleMania::MarbleMania(int players, int marbles)
  : current_index(0),
    current_value(1),
    current_player(0),
    player_count(players),
    marble_count(marbles),
    marbles { 0 },
    scores(players)
{}

void MarbleMania::rotate_by_num(std::vector<int>& v, int n) {
  for (int i = 0; i < abs(n); i++ ){
    if (n < 0){
      std::rotate(v.begin(), v.begin() + v.size() - 1, v.end());
    } else {
      std::rotate(v.begin(), v.begin() + 1, v.end());
    }
  }
}

void MarbleMania::rotate_by_num(std::list<int>& v, int n) {
  for (int i = 0; i < abs(n); i++ ){
    if (n < 0){
      v.push_front(v.back());
      v.pop_back();
    } else {
      v.push_back(v.front());
      v.pop_front();
    }
  }
}

void MarbleMania::take_turn() {

  if(current_value % 23 == 0){
    scores[current_player] += current_value;

    rotate_by_num(marbles, -7);

    if(marbles.front() < 0) std::cerr << "wtf at" << current_value;
    scores[current_player] += marbles.front();
    marbles.pop_front();
  } else {

  rotate_by_num(marbles, 2);

  marbles.push_front(current_value);
}
  current_value++;

  current_player++;
  current_player %= player_count;
}

void MarbleMania::run_game() {
  for(int i = 1; i <= marble_count; i++){
    // if( i % 1000 == 0) std::cerr << "boy howdy i'm doin " << i << std::endl;
    take_turn();
  }
}

unsigned int MarbleMania::high_score() {
  auto high_score = std::max_element(scores.begin(), scores.end());
  return *high_score;
}

