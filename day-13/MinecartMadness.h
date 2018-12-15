#ifndef DAY_13
#define DAY_13

#include "../utils/Point.h"

#include <string>
#include <vector>

namespace MinecartMadness {

  static const utils::Point LEFT { -1, 0 };
  static const utils::Point RIGHT { 1, 0 };
  static const utils::Point UP { 0, -1 };
  static const utils::Point DOWN { 0, 1 };

  class Cart {
  public:
    Cart(int loc_x, int loc_y, int dir_x, int dir_y) : location { loc_x, loc_y }, direction { dir_x, dir_y } {}
    Cart(int loc_x, int loc_y, utils::Point initial_dir) : location { loc_x, loc_y }, direction (initial_dir) {}
    utils::Point location;
    utils::Point direction;
  };

  class MinecartSimulation {
  public:

    MinecartSimulation(std::vector<std::string> gameboard);
    void simulate();
    void find_carts();
    // find crash
    // check for crash

    std::vector<Cart> carts;
    std::vector<std::string> board;
  };
}

#endif
