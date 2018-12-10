#ifndef DAY_09
#define DAY_09

#include <vector>
#include <map>

class MarbleMania {
public:
  MarbleMania(int players, int marbles);
  void run_game();

  void take_turn();
  int high_score();

  int current_index;
  int current_value;
  int current_player;
  int player_count;
  int marble_count;
  std::vector<int> marbles;
  std::vector<int> scores;
};

#endif
