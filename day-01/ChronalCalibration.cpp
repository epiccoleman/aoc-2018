#include "ChronalCalibration.h"

#include <numeric>
#include <set>

int ChronalCalibration::chronal_calibration_part_1(const std::vector<int> frequencies){
  return std::accumulate(frequencies.begin(), frequencies.end(), 0);
}

int ChronalCalibration::chronal_calibration_part_2(const std::vector<int> frequencies){
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
