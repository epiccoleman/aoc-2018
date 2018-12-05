#pragma once

#include <string>
#include <vector>

namespace InventoryManagement {
  bool contains_n_occurences(const int n, const std::string id);
  int inventory_checksum(const std::vector<std::string> ids);

  int count_differences(const std::string a, const std::string b);
  std::string common_letters(const std::string a, const std::string b);
  std::string find_similar_boxes_difference(const std::vector<std::string> ids);
};
