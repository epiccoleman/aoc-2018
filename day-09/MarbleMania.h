#ifndef DAY_09
#define DAY_09

#include <vector>
#include <list>
#include <map>

class MarbleMania {
public:
  MarbleMania(int players, int marbles);
  void run_game();

  unsigned int high_score();

  static void rotate_by_num(std::list<int>& v, int n);

private:
  void take_turn();

  int current_player;
  int current_value;
  int player_count;
  int marble_count;
  std::list<int> marbles;
  std::vector<unsigned int> scores;
};

#endif
