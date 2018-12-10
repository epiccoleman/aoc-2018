#include "MarbleMania.h"
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

void MarbleMania::take_turn() {

  if(current_value % 23 == 0){
    scores[current_player] += current_value;

    current_index -= 7;
    current_index %= marbles.size();

    auto it = marbles.begin() + current_index;

    scores[current_player] += *it;
    marbles.erase(it);
  } else {

  current_index += 2;
  current_index %= marbles.size();

  if(marbles.size() == 1){
    current_index++;
  }

  if (current_index == marbles.size()){ // we're adding to the end
    marbles.push_back(current_value);
  } else {
    auto it = marbles.begin() + current_index;
    marbles.insert(it, current_value);
  }
}
  current_value++;

  current_player++;
  current_player %= player_count;
}

void MarbleMania::run_game() {
  for(int i = 1; i <= marble_count; i++){
    take_turn();
  }
}

int MarbleMania::high_score() {
  auto high_score = std::max_element(scores.begin(), scores.end());
  return *high_score;
}

