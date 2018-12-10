#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "MarbleMania.h"

TEST(MarbleManiaTest, highscore){
  MarbleMania test(9, 25);
  test.run_game();

  EXPECT_EQ(test.high_score(), 32);
}

TEST(MarbleManiaTest, trivial){
  MarbleMania test(9, 1);
  test.run_game();
  
  std::vector<int> expected { 0, 1 };

  EXPECT_EQ(test.marbles, expected);
  EXPECT_EQ(test.current_index, 1);
}

TEST(MarbleManiaTest, lessTrivial){
  MarbleMania test(9, 2);
  test.run_game();
  
  std::vector<int> expected { 0, 2, 1 };

  EXPECT_EQ(test.marbles, expected);
  EXPECT_EQ(test.current_index, 1);
}

TEST(MarbleManiaTest, worksFor3){
  MarbleMania test(9, 3);
  test.run_game();
  
  std::vector<int> expected { 3, 0, 2, 1 };

  EXPECT_EQ(test.marbles, expected);
}

TEST(MarbleManiaTest, non23CaseWorks){
  MarbleMania test(9, 5);
  test.run_game();
  
  std::vector<int> expected { 3, 0, 4, 2, 5, 1 };

  EXPECT_EQ(test.marbles, expected);
}

// 13 players; last marble is worth 7999 points: high score is 146373
// 17 players; last marble is worth 1104 points: high score is 2764
// 21 players; last marble is worth 6111 points: high score is 54718
// 30 players; last marble is worth 5807 points: high score is 37305

TEST(MarbleManiaTest, scoreTest1){
  MarbleMania test(10, 1618);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 8317);
}

TEST(MarbleManiaTest, scoreTest2){
  MarbleMania test(13, 7999);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 146380);
}

TEST(MarbleManiaTest, solvePart1){
  MarbleMania test(452, 71250);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 388844);
}

TEST(MarbleManiaTest, solvePart2){

  MarbleMania test(452, 7125000);
  test.run_game();
  
  EXPECT_EQ(test.high_score(), 146373);
}
