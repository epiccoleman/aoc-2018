#ifndef DAY_09
#define DAY_09

#include <vector>
#include <list>
#include <map>

class MarbleMania {
public:
  MarbleMania(int players, int marbles);
  void run_game();

  void take_turn();
  unsigned int high_score();

  int current_index;
  int current_value;
  int current_player;
  int player_count;
  int marble_count;
  std::list<int> marbles;
  std::vector<unsigned int> scores;

  static void rotate_by_num(std::vector<int>& v, int n);
  static void rotate_by_num(std::list<int>& v, int n);
};

#endif
