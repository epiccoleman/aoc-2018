#ifndef DAY_10
#define DAY_10

#include "../utils/Point.h"
#include <vector>
#include <string>

namespace StarAlignment {
  class Star {
  public:
    Star(utils::Point p, utils::Point v);
    Star(int p_x, int p_y, int v_x, int v_y);
    utils::Point position;
    utils::Point velocity;

    void advance_position(); 
  };

  bool possible_hit(std::vector<Star> stars, int time);
  void advance_stars(std::vector<Star>& stars);

  std::vector<Star> slurp_input();
}

#endif
