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
    Cart(int loc_x, int loc_y, utils::Point initial_dir);

    void advance(char road_type);
    void advance();

    void handle_forward_slash();
    void handle_back_slash();
    void handle_crossroads();
    void mark_for_deletion();
    void turn_left();
    void turn_right();
    utils::Point next_location();

    int next_crossroad_dir;
    utils::Point location;
    utils::Point direction;
    bool crashed;
  };

  class MinecartSimulation {
  public:

    MinecartSimulation(std::vector<std::string> gameboard);

    void find_carts();
    bool crash_at(utils::Point loc);
    void mark_carts_at_loc_for_deletion(utils::Point loc);
    void remove_marked_carts();
    void log_crash(utils::Point loc);
    void sort_carts();


    void simulate();
    utils::Point find_first_crash();
    utils::Point find_last_cart();


    std::vector<Cart> carts;
    std::vector<utils::Point> crashes;
    const std::vector<std::string> board;
  };
}

#endif
