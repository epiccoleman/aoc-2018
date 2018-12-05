#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "../utils.h"

#include "ChronalCalibration.h"

TEST(ChronalCalibrationTest, calibration1){
  std::vector<int> test1 { 1, 1, 1 };
  std::vector<int> test2 { 1, 1, -2 };
  std::vector<int> test3 { -1, -2, -3 };

  EXPECT_EQ(ChronalCalibration::chronal_calibration_part_1(test1), 3);
  EXPECT_EQ(ChronalCalibration::chronal_calibration_part_1(test2), 0);
  EXPECT_EQ(ChronalCalibration::chronal_calibration_part_1(test3), -6);
}

TEST(ChronalCalibrationTest, calibration2){
  std::vector<int> test1 { 1, -1 };
  std::vector<int> test2 { 3, 3, 4, -2, -4 };
  std::vector<int> test3 { -6, 3, 8, 5, -6 };

  EXPECT_EQ(ChronalCalibration::chronal_calibration_part_2(test1), 0);
  EXPECT_EQ(ChronalCalibration::chronal_calibration_part_2(test2), 10);
  EXPECT_EQ(ChronalCalibration::chronal_calibration_part_2(test3), 5);
}

TEST(ChronalCalibrationTest, solvePart1){
  std::vector<int> frequencies = utils::slurp_file_as_ints("input.txt");

  int result = ChronalCalibration::chronal_calibration_part_1(frequencies);

  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 505);
}

TEST(ChronalCalibrationTest, solvePart2){
  std::vector<int> frequencies = utils::slurp_file_as_ints("input.txt");

  int result = ChronalCalibration::chronal_calibration_part_2(frequencies);

  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, 72330);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
