#include "ChronalCalibration.h"

#include <numeric>
#include <set>

int ChronalCalibration::sum_frequencies(const std::vector<int> frequencies){
  return std::accumulate(frequencies.begin(), frequencies.end(), 0);
}

int ChronalCalibration::find_first_repeated_frequency(const std::vector<int> frequencies){
  int frequency = 0;
  std::set<int> seen_values;
  bool found = false;

  while(!found){
    for( auto delta : frequencies){
      if(! seen_values.insert(frequency).second){
        found = true;
        break;
      }
      frequency += delta;
    }
  }

  return frequency;
}
