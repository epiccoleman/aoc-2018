#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "MarbleMania.h"

TEST(MarbleManiaTest, highscore){
  MarbleMania test(9, 25);
  test.run_game();

  EXPECT_EQ(test.high_score(), 32);
}

TEST(MarbleManiaTest, scoreTest1){
  MarbleMania test(10, 1618);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 8317);
}

TEST(MarbleManiaTest, scoreTest2){
  MarbleMania test(13, 7999);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 146373);
}

TEST(MarbleManiaTest, solvePart1){
  MarbleMania test(452, 71250);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 388844);
}

TEST(MarbleManiaTest, solvePart2){

  MarbleMania test(452, 7125000);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 3212081616);
}
