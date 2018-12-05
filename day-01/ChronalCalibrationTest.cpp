#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "../utils/utils.h"

#include "ChronalCalibration.h"

TEST(ChronalCalibrationTest, calibration1){
  std::vector<int> test1 { 1, 1, 1 };
  std::vector<int> test2 { 1, 1, -2 };
  std::vector<int> test3 { -1, -2, -3 };

  EXPECT_EQ(ChronalCalibration::sum_frequencies(test1), 3);
  EXPECT_EQ(ChronalCalibration::sum_frequencies(test2), 0);
  EXPECT_EQ(ChronalCalibration::sum_frequencies(test3), -6);
}

TEST(ChronalCalibrationTest, calibration2){
  std::vector<int> test1 { 1, -1 };
  std::vector<int> test2 { 3, 3, 4, -2, -4 };
  std::vector<int> test3 { -6, 3, 8, 5, -6 };

  EXPECT_EQ(ChronalCalibration::find_first_repeated_frequency(test1), 0);
  EXPECT_EQ(ChronalCalibration::find_first_repeated_frequency(test2), 10);
  EXPECT_EQ(ChronalCalibration::find_first_repeated_frequency(test3), 5);
}

TEST(ChronalCalibrationTest, solvePart1){
  std::vector<int> frequencies = utils::slurp_file_as_ints("day-01/input.txt");

  int result = ChronalCalibration::sum_frequencies(frequencies);

  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 505);
}

TEST(ChronalCalibrationTest, solvePart2){
  std::vector<int> frequencies = utils::slurp_file_as_ints("day-01/input.txt");

  int result = ChronalCalibration::find_first_repeated_frequency(frequencies);

  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, 72330);
}
