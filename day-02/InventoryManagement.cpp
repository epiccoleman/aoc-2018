#include "InventoryManagement.h"

#include <set>
#include <algorithm>

bool InventoryManagement::contains_n_occurences(const int n, const std::string id){

  std::set<char> char_set;
  for (char c : id){
    char_set.insert(c);
  }

  for (char c : char_set){
    if(std::count(id.begin(), id.end(), c) == n) return true;
  }

  return false;
}

int InventoryManagement::inventory_checksum(const std::vector<std::string> ids){
  int count_two_occurences = std::count_if(ids.begin(), ids.end(),
                                           [](std::string id){ return contains_n_occurences(2, id);});
  int count_three_occurences = std::count_if(ids.begin(), ids.end(),
                                             [](std::string id){ return contains_n_occurences(3, id);});

  return count_two_occurences * count_three_occurences;
}

int InventoryManagement::count_differences(const std::string a, const std::string b){
  int difference_count = 0;
  for(int i = 0; i < a.size(); i++){
    if(a[i] != b[i]) difference_count++;
  }
  return difference_count;
}

std::string InventoryManagement::common_letters(const std::string a, const std::string b){
  std::string common_letters = "";
  for(int i = 0; i < a.size(); i++){
    if(a[i] == b[i]) common_letters += a[i];
  }

  return common_letters;
};

std::string InventoryManagement::find_similar_boxes_difference(const std::vector<std::string> ids) {
  for(std::string id_a : ids){
    for(std::string id_b : ids){
      if(count_differences(id_a, id_b) == 1) return common_letters(id_a, id_b);
    }
  }
  return ""; 
}
