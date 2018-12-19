#ifndef DAY_18
#define DAY_18

#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <utility>
#include <iostream>

namespace GameOfLumber {
  static const char TREE = '|';
  static const char OPEN = '.';
  static const char LUMBER = '#';

  using Board = std::vector<std::string>;
  struct ResourceCount {
    ResourceCount() : tree_count(0), open_count(0), lumber_count(0) {} // sigh
    int tree_count;
    int open_count;
    int lumber_count;
    int value() { return tree_count * lumber_count; }
  };

  bool check_index_validity(int x, int y, int max_x, int max_y){
    return 0 <= x && x < max_x && 0 <= y && y < max_y;
  }

  ResourceCount count_neighbors(const int x, const int y, const Board& board){
    ResourceCount count;
    for(int j = y - 1; j <= y + 1; j++){
      for(int i = x - 1; i <= x + 1; i++){

        if(check_index_validity(i, j, board[j].size(), board.size()) && !(j == y && i == x)){
          switch (board[j][i]) {
          case '|':
            count.tree_count += 1;
            break;
          case '.':
            count.open_count += 1;
            break;
          case '#':
            count.lumber_count += 1;
            break;
          }
        }
      }
    }
    return count;
  }

  ResourceCount count_resources(const Board& board){
    ResourceCount count;
    for(auto row : board){
      for(auto col : row){
        switch (col) {
        case '|':
          count.tree_count += 1;
          break;
        case '.':
          count.open_count += 1;
          break;
        case '#':
          count.lumber_count += 1;
          break;
        }
      }
    }
    return count;
  }

  char next_state(const char c, const int x, const int y, const Board& board){
    auto count = count_neighbors(x, y, board);

    if (c == OPEN && count.tree_count >= 3) return '|';
    if (c == TREE && count.lumber_count >= 3) return '#';
    if (c == LUMBER && !(count.tree_count >= 1 && count.lumber_count >= 1)) return '.';
    return c;
  }

  Board step(const Board& board){
    std::vector<std::string> new_board(board.size(), std::string(board[0].size(), ' '));

    for(int y = 0; y < board.size(); y++){
      for(int x = 0; x < board[y].size(); x++){
        new_board[y][x] = next_state(board[y][x], x, y, board);
      }
    }
    return new_board;
  }

  Board simulate(const Board& board, int minutes){
    Board new_board = board;
    for (int i = 0 ; i < minutes; i++){
      new_board = step(new_board);
    }
    return new_board;
  }

  int simulate_with_cycle(const Board& board, int minutes){
    Board new_board = board;
    std::set<std::pair<int, int > > seen_values;
    std::vector<int> resource_values;
    int first_value_in_cycle = -1;
    int cycle_start_pos = -1;

    for (int i = 0 ; i < minutes; i++){
      std::pair<int, int> current;
      current.first = count_resources(new_board).value();
      new_board = step(new_board);
      current.second = count_resources(new_board).value();
      auto insert_result = seen_values.insert(current);
      if (!insert_result.second){  // found first value in the cycle
        first_value_in_cycle = current.first;
        cycle_start_pos = i;
        break;
      }
      resource_values.push_back(current.first);
    }

    std::vector<int> cycle_values;
    auto cycle_start = std::find(resource_values.begin(), resource_values.end(), first_value_in_cycle);
    std::copy(cycle_start, resource_values.end(), std::back_inserter(cycle_values));

    int cycle_pos = (minutes - cycle_start_pos) % cycle_values.size();
    return cycle_values[cycle_pos];
  }
}

#endif
