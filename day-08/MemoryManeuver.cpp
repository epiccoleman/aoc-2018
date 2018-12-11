#include "MemoryManeuver.h"

#include <numeric>

MemoryManeuver::memory_node MemoryManeuver::parse_input_from_list(std::list<int>& input) {
  // put first two elements into header
  memory_node root;

  root.children_count = input.front();
  input.pop_front();
  root.metadata_count = input.front();
  input.pop_front();

  for (int i = 0; i < root.children_count; i++){
    root.children.push_back(parse_input_from_list(input));
  }

  for (int i = 0; i < root.metadata_count; i++){
    root.metadata.push_back(input.front());
    input.pop_front();
  }

  return root;
}

int MemoryManeuver::sum_metadata(const memory_node root) {

  int sum = std::accumulate(root.metadata.begin(), root.metadata.end(), 0);

  for (auto node : root.children) {
    sum += sum_metadata(node);
  }

  return sum;
}

int MemoryManeuver::node_value(const memory_node root) {

  if (root.children.empty()) {
    return std::accumulate(root.metadata.begin(), root.metadata.end(), 0);
  }
  else {
    int sum = 0;
    for (int index : root.metadata) {
      if (index <= root.children.size()){
        sum += node_value(root.children[index - 1]);
      }
    }
    return sum;
  }
}
