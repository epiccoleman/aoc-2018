#include <gtest/gtest.h>
#include "utils.h"

TEST(UtilsTest, slurp_file_linesWithEmptyLinesInputDoesNotRemoveEmptyLines){
  //first 5 lines of input
  // 2 0 0 1
  // 11 1 0 2
  // 2 0 1 1
  //
  // 1 3 2 3

  auto slurp = utils::slurp_file_lines("utils/input-with-blank-lines.txt");

  EXPECT_EQ(slurp[2], "2 0 1 1");
  EXPECT_EQ(slurp[3], "");
  EXPECT_EQ(slurp[4], "1 3 2 3");
}

TEST(UtilsTest, slurp_file_tokensDontCareAboutNewlines){
  //first 5 lines of input
  // 2 0 0 1
  // 11 1 0 2
  // 2 0 1 1
  //
  // 1 3 2 3

  auto slurp = utils::slurp_file_as_ints("utils/input-with-blank-lines.txt");

  EXPECT_EQ(slurp[10], 1);
  EXPECT_EQ(slurp[11], 1);
  EXPECT_EQ(slurp[12], 1);
  EXPECT_EQ(slurp[13], 3);
}
