#ifndef DAY_08
#define DAY_08

#include <list>
#include <vector>

namespace MemoryManeuver {

  struct memory_node {

    int children_count;
    int metadata_count;

    std::vector<memory_node> children;
    std::vector<int> metadata;
  };

  memory_node parse_input_from_list(std::list<int>& input);
  int sum_metadata(const memory_node root);
  int node_value(const memory_node root);
}

#endif
