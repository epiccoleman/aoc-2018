#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "MinecartMadness.h"

TEST(MinecartMadnessTest, getsCartsCorrectly){
  std::vector<std::string> testBoard { "/-->-\\" ,
                                       "|    |",
                                      "\\-<--/" };

  MinecartMadness::MinecartSimulation test(testBoard);

  EXPECT_EQ(test.carts.size(), 2);
}

TEST(MinecartMadnessTest, advanceHandlesVerticalRoadsMovingUpward){
  std::vector<std::string> testBoard
  { "|",
    "|",
    "^" };

  MinecartMadness::Cart cart(0, 2, MinecartMadness::UP, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 1};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, advanceHandlesVerticalRoadsMovingDownward){
  std::vector<std::string> testBoard
  { "|",
      "|",
      "^" };

  MinecartMadness::Cart cart(0, 1, MinecartMadness::DOWN, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 2};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, advanceHandlesHorizontalRoadsMovingRight){
  std::vector<std::string> testBoard
  { "---" };

  MinecartMadness::Cart cart(1, 0, MinecartMadness::RIGHT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{2, 0};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, advanceHandlesHorizontalRoadsMovingLeft){
  std::vector<std::string> testBoard
  { "---" };

  MinecartMadness::Cart cart(1, 0, MinecartMadness::LEFT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingUpDirectionBecomesRight){
  std::vector<std::string> testBoard
  { "/",
    "|" };

  MinecartMadness::Cart cart(0, 1, MinecartMadness::UP, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::RIGHT);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingDownDirectionBecomesLeft){
  std::vector<std::string> testBoard
  { "|",
    "/" };

  MinecartMadness::Cart cart(0, 0, MinecartMadness::DOWN, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 1};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::LEFT);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingLeftDirectionBecomesDown){
  std::vector<std::string> testBoard { "/-" };

  MinecartMadness::Cart cart(1, 0, MinecartMadness::LEFT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::DOWN);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingRightDirectionBecomesUp){
  std::vector<std::string> testBoard { "-/" };

  MinecartMadness::Cart cart(0, 0, MinecartMadness::RIGHT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{1, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingUpDirectionBecomesLeft){
  std::vector<std::string> testBoard
  { "\\",
    "|" };

  MinecartMadness::Cart cart(0, 1, MinecartMadness::UP, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::LEFT);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingDownDirectionBecomesRight){
  std::vector<std::string> testBoard
  { "|",
    "\\" };

  MinecartMadness::Cart cart(0, 0, MinecartMadness::DOWN, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 1};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::RIGHT);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingLeftDirectionBecomesUp){
  std::vector<std::string> testBoard { "\\-" };

  MinecartMadness::Cart cart(1, 0, MinecartMadness::LEFT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingRightDirectionBecomesDown){
  std::vector<std::string> testBoard { "-\\" };

  MinecartMadness::Cart cart(0, 0, MinecartMadness::RIGHT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{1, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::DOWN);
}

TEST(MinecartMadnessTest, crossroadsTest){
  std::vector<std::string> testBoard
  { "+++" ,
    "++-",
    "-+-" };

  MinecartMadness::Cart cart(0, 2, MinecartMadness::RIGHT, testBoard);

  cart.advance();

  auto expected_loc = utils::Point{1, 2};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);

  cart.advance();

  expected_loc = utils::Point{1, 1};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);

  cart.advance();

  expected_loc = utils::Point{1, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::RIGHT);

  cart.advance();

  expected_loc = utils::Point{2, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);
}

TEST(MinecartMadnessTest, canDetectDuplicatePair){
  std::vector<std::string> testBoard
  { "+++" ,
      "++-",
      "-+-" };

  MinecartMadness::MinecartSimulation sim(testBoard);

  sim.carts = std::vector<MinecartMadness::Cart> { MinecartMadness::Cart(0, 2, MinecartMadness::RIGHT, testBoard),
                 MinecartMadness::Cart(0, 2, MinecartMadness::RIGHT, testBoard)};

  EXPECT_EQ(sim.find_first_crash().first, 0);
  EXPECT_EQ(sim.find_first_crash().second, 2);
}

TEST(MinecartMadnessTest, simulateUpdatesCartLocations){
  std::vector<std::string> board = { ">-----" };

  MinecartMadness::MinecartSimulation sim(board);
  EXPECT_EQ(sim.carts[0].location.x, 0);
  sim.simulate();
  EXPECT_EQ(sim.carts[0].location.x, 1);
  sim.simulate();
  EXPECT_EQ(sim.carts[0].location.x, 2);
}

TEST(MinecartMadnessTest, simpleCrash){
  std::vector<std::string> board = { ">-----<" };

  MinecartMadness::MinecartSimulation sim(board);

  EXPECT_EQ(sim.find_first_crash().first, 3);
}

TEST(MinecartMadnessTest, solveDay1){
  std::vector<std::string> board = utils::slurp_file_lines("day-13/input.txt");

  MinecartMadness::MinecartSimulation sim(board);

  EXPECT_EQ(sim.find_first_crash().first, 0);
  EXPECT_EQ(sim.find_first_crash().second, 2);
}
