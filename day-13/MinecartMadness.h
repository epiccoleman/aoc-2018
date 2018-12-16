#ifndef DAY_13
#define DAY_13

#include "../utils/Point.h"

#include <string>
#include <vector>
#include <utility>

namespace MinecartMadness {

  static const utils::Point LEFT { -1, 0 };
  static const utils::Point RIGHT { 1, 0 };
  static const utils::Point UP { 0, -1 };
  static const utils::Point DOWN { 0, 1 };

  class Cart {
  public:
    Cart(int loc_x, int loc_y, utils::Point initial_dir, const std::vector<std::string>& b) : location { loc_x, loc_y }, direction (initial_dir), board(b), next_crossroad_dir(0) {}

    void advance();

    void handle_forward_slash();
    void handle_back_slash();
    void handle_crossroads();
    void turn_left();
    void turn_right();

    int next_crossroad_dir;
    const std::vector<std::string>& board;
    const std::vector<utils::Point> crashes;
    utils::Point location;
    utils::Point direction;
  };

  class MinecartSimulation {
  public:

    MinecartSimulation(std::vector<std::string> gameboard);
    void simulate();
    void find_carts();
    std::pair<int, int> find_first_crash();

    // find crash
    // check for crash

    std::vector<Cart> carts;
    std::vector<std::string> board;
  };
}

#endif
