#include "AlchemicalReduction.h"
#include <algorithm>
#include <vector>

bool AlchemicalReduction::reactable(std::string polymer) {
  for ( int i = 0; i < polymer.size() - 1; i++){
    if (abs(polymer[i] - polymer[i + 1]) == 32) return true;
  }
  return false;
}

std::string AlchemicalReduction::react(std::string polymer) {

  while(reactable(polymer)){
    for ( int i = 0; i < polymer.size() - 1; i++){
      if (abs(polymer[i] - polymer[i + 1]) == 32){
        polymer.erase(i, 2);
      }
    }
  }

  return polymer;
}

std::string AlchemicalReduction::filter_unit(std::string polymer, char unit) {
  polymer.erase(std::remove_if(polymer.begin(),
                            polymer.end(),
                            [unit](char x){
                              return x == toupper(unit) || x == tolower(unit);}),
                polymer.end());

  return polymer;
}

int AlchemicalReduction::shortest_polymer(const std::string polymer) {
  std::string abcs = "abcdefghijklmnopqrstuvwxyz";
  std::vector<int> results;

  for (auto c : abcs) {
    std::string filtered = filter_unit(polymer, c);
    results.push_back(react(filter_unit(polymer, c)).size()); 
  }

  return *std::min_element(results.begin(), results.end());
}
