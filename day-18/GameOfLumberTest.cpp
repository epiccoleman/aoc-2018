#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "GameOfLumber.h"

TEST(GameOfLumberTest, countNeighbors){
  GameOfLumber::Board testBoard { "|||",
                                  "...",
                                  "###" };

  auto counts = GameOfLumber::count_neighbors(1,1, testBoard);
  EXPECT_EQ(counts.tree_count, 3);
  EXPECT_EQ(counts.open_count, 2);
  EXPECT_EQ(counts.lumber_count, 3);
}

TEST(GameOfLumberTest, countNeighborsWorksProperlyOnEdges){
  GameOfLumber::Board testBoard { "|||",
                                  "...",
                                  "###" };

  auto counts = GameOfLumber::count_neighbors(0, 1, testBoard);
  EXPECT_EQ(counts.tree_count, 2);
  EXPECT_EQ(counts.open_count, 1);
  EXPECT_EQ(counts.lumber_count, 2);
}

TEST(GameOfLumberTest, countResources){
  GameOfLumber::Board testBoard { "|||",
                                  "...",
                                  "###" };

  auto counts = GameOfLumber::count_resources(testBoard);
  EXPECT_EQ(counts.tree_count, 3);
  EXPECT_EQ(counts.open_count, 3);
  EXPECT_EQ(counts.lumber_count, 3);
}

TEST(GameOfLumberTest, nextStateOpenToOpen){
  GameOfLumber::Board testBoard { "...",
                                  "...",
                                  "..." };

  auto new_state = GameOfLumber::next_state(testBoard[1][1], 1, 1, testBoard);
  EXPECT_EQ(new_state, '.');
}

TEST(GameOfLumberTest, nextStateOpenToTree){
  GameOfLumber::Board testBoard { ".||",
                                  "..|",
                                  "..|" };

  auto new_state = GameOfLumber::next_state(testBoard[1][1], 1, 1, testBoard);
  EXPECT_EQ(new_state, '|');
}

TEST(GameOfLumberTest, nextStateTreeToTree){
  GameOfLumber::Board testBoard { ".||",
                                  ".|.",
                                  "..." };

  auto new_state = GameOfLumber::next_state(testBoard[1][1], 1, 1, testBoard);
  EXPECT_EQ(new_state, '|');
}

TEST(GameOfLumberTest, nextStateTreeToLumber){
  GameOfLumber::Board testBoard { ".##",
                                  ".|#",
                                  "..." };

  auto new_state = GameOfLumber::next_state(testBoard[1][1], 1, 1, testBoard);
  EXPECT_EQ(new_state, '#');
}

TEST(GameOfLumberTest, nextStateLumberToLumber){
  GameOfLumber::Board testBoard { ".#|",
                                  ".#.",
                                  "..." };

  auto new_state = GameOfLumber::next_state(testBoard[1][1], 1, 1, testBoard);
  EXPECT_EQ(new_state, '#');
}

TEST(GameOfLumberTest, nextStateLumberToOpen){
  GameOfLumber::Board testBoard { "...",
                                  ".#.",
                                  "..." };

  auto new_state = GameOfLumber::next_state(testBoard[1][1], 1, 1, testBoard);
  EXPECT_EQ(new_state, '.');
}

TEST(GameOfLumberTest, check_index_validity){
  EXPECT_FALSE(GameOfLumber::check_index_validity(-1, 0, 5, 5));
  EXPECT_FALSE(GameOfLumber::check_index_validity(0, 10, 5, 5));
  EXPECT_TRUE(GameOfLumber::check_index_validity(0, 0, 5, 5));
  EXPECT_TRUE(GameOfLumber::check_index_validity(1, 1, 5, 5));
}
TEST(GameOfLumberTest, simulate){
  
  GameOfLumber::Board before { "....#",
                               ".##.|",
                               "#||||" };

  GameOfLumber::Board after  { ".....",
                               ".##||",
                               "##|||" };

  std::cerr << before[0][3];
  auto new_state = GameOfLumber::step(before);
  EXPECT_EQ(new_state, after);
}

TEST(GameOfLumberTest, solvePart1){
  std::vector<std::string> board = utils::slurp_file_lines("day-18/input.txt");

  auto resources =
    GameOfLumber::count_resources (GameOfLumber::simulate(board, 10));

  int result = resources.value();
  
  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 384480);
}

TEST(GameOfLumberTest, solvePart2){
  std::vector<std::string> board = utils::slurp_file_lines("day-18/input.txt");


  int result = GameOfLumber::simulate_with_cycle(board, 1000000000);
  
  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, 177004);
}
