#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "MinecartMadness.h"

TEST(MinecartMadnessTest, getsCartsCorrectly){
  std::vector<std::string> testBoard { "/-->-\\" ,
                                       "|    |",
                                      "\\-<--/" };

  MinecartMadness::MinecartSimulation test(testBoard);

  EXPECT_EQ(test.carts.size(), 2);
  EXPECT_EQ(test.carts[0].location.x, 3);
  EXPECT_EQ(test.carts[0].location.y, 0);
  EXPECT_EQ(test.carts[1].location.x, 2);
  EXPECT_EQ(test.carts[1].location.y, 2);
}

// TEST(MinecartMadnessTest, lessSimpleLoad){
//   std::vector<std::string> board =
//     { "/>-<\\  ", //  "/>-<\  "
//       "|   |  ",  //  "|   |  "
//       "| /<+-\\", //  "| /<+-\"
//       "| | | v",  //  "| | | v"
//       "\\>+</ |", //  "\>+</ |"
//       "  |   ^",  //  "  |   ^"
//       "  \\<->/" };// "  \<->/"

//   MinecartMadness::MinecartSimulation sim(board);

//   for(const auto cart : sim.carts ){
//     std::cout << "cart at: " << cart.location.x << "." << cart.location.y << "." << std::endl;
//     std::cout << "--  dir: " << cart.direction.x << "." << cart.direction.y << std::endl;
//   }
//   sim.simulate();
//   for(const auto cart : sim.carts ){
//     std::cout << "cart at: " << cart.location.x << "." << cart.location.y << "." << std::endl;
//     std::cout << "--  dir: " << cart.direction.x << "." << cart.direction.y << std::endl;
//   }

// }

TEST(MinecartMadnessTest, advanceHandlesVerticalRoadsMovingUpward){
  MinecartMadness::Cart cart(0, 2, MinecartMadness::UP);

  cart.advance('|');

  auto expected_loc = utils::Point{0, 1};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, advanceHandlesVerticalRoadsMovingDownward){
  MinecartMadness::Cart cart(0, 1, MinecartMadness::DOWN);

  cart.advance('|');

  auto expected_loc = utils::Point{0, 2};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, advanceHandlesHorizontalRoadsMovingRight){
  MinecartMadness::Cart cart(1, 0, MinecartMadness::RIGHT);

  cart.advance('-');

  auto expected_loc = utils::Point{2, 0};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, advanceHandlesHorizontalRoadsMovingLeft){
  MinecartMadness::Cart cart(1, 0, MinecartMadness::LEFT);

  cart.advance('-');

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingUpDirectionBecomesRight){
  MinecartMadness::Cart cart(0, 1, MinecartMadness::UP);

  cart.advance('/');

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::RIGHT);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingDownDirectionBecomesLeft){
  MinecartMadness::Cart cart(0, 0, MinecartMadness::DOWN);

  cart.advance('/');

  auto expected_loc = utils::Point{0, 1};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::LEFT);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingLeftDirectionBecomesDown){
  MinecartMadness::Cart cart(1, 0, MinecartMadness::LEFT);

  cart.advance('/');

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::DOWN);
}

TEST(MinecartMadnessTest, whenEnteringForwardSlashMovingRightDirectionBecomesUp){
  MinecartMadness::Cart cart(0, 0, MinecartMadness::RIGHT);

  cart.advance('/');

  auto expected_loc = utils::Point{1, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingUpDirectionBecomesLeft){
  MinecartMadness::Cart cart(0, 1, MinecartMadness::UP);

  cart.advance('\\');

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::LEFT);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingDownDirectionBecomesRight){
  MinecartMadness::Cart cart(0, 0, MinecartMadness::DOWN);

  cart.advance('\\');

  auto expected_loc = utils::Point{0, 1};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::RIGHT);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingLeftDirectionBecomesUp){
  MinecartMadness::Cart cart(1, 0, MinecartMadness::LEFT);

  cart.advance('\\');

  auto expected_loc = utils::Point{0, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);
}

TEST(MinecartMadnessTest, whenEnteringBackSlashMovingRightDirectionBecomesDown){
  MinecartMadness::Cart cart(0, 0, MinecartMadness::RIGHT);

  cart.advance('\\');

  auto expected_loc = utils::Point{1, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::DOWN);
}

TEST(MinecartMadnessTest, crossroadsTest){
  MinecartMadness::Cart cart(0, 2, MinecartMadness::RIGHT);

  cart.advance('+');

  auto expected_loc = utils::Point{1, 2};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);

  cart.advance('+');

  expected_loc = utils::Point{1, 1};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);

  cart.advance('+');

  expected_loc = utils::Point{1, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::RIGHT);

  cart.advance('+');

  expected_loc = utils::Point{2, 0};

  EXPECT_EQ(cart.location, expected_loc);
  EXPECT_EQ(cart.direction, MinecartMadness::UP);
}

TEST(MinecartMadnessTest, canDetectCrash){
  std::vector<std::string> board = { ">-" };
  MinecartMadness::MinecartSimulation sim(board);
  utils::Point crash { 0, 0 } ;
  EXPECT_TRUE(sim.crash_at(crash));
  utils::Point not_crash { 0, 1 } ;
  EXPECT_FALSE(sim.crash_at(not_crash));
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

  EXPECT_EQ(sim.carts.size(), 2);
  EXPECT_EQ(sim.find_first_crash().x, 3);
  EXPECT_EQ(sim.carts.size(), 0);
}

TEST(MinecartMadnessTest, lessSimpleCrash){
  std::vector<std::string> board =
    { "/>-<\\  ", //  "/>-<\  "
      "|   |  ",  //  "|   |  "
      "| /<+-\\", //  "| /<+-\"
      "| | | v",  //  "| | | v"
      "\\>+</ |", //  "\>+</ |"
      "  |   ^",  //  "  |   ^"
      "  \\<->/" };// "  \<->/"

  MinecartMadness::MinecartSimulation sim(board);

  EXPECT_EQ(sim.carts.size(), 9);
  EXPECT_EQ(sim.find_last_cart().x, 6);
  EXPECT_EQ(sim.find_last_cart().y, 4);
  EXPECT_EQ(sim.carts.size(), 1);
}

TEST(MinecartMadnessTest, anotherCrash){
  std::vector<std::string> board =
    { 
"/->--->>--\\   /-----<->----\\",
"|         |   |            |",
"\\---------/   \\------------/"

      };

  MinecartMadness::MinecartSimulation sim(board);

  EXPECT_EQ(sim.carts.size(), 5);
  EXPECT_EQ(sim.find_last_cart().x, 6);
  EXPECT_EQ(sim.find_last_cart().y, 2);
  EXPECT_EQ(sim.carts.size(), 1);
}

TEST(MinecartMadnessTest, solvePart1){
  std::vector<std::string> board = utils::slurp_file_lines("day-13/input.txt");

  MinecartMadness::MinecartSimulation sim(board);
  EXPECT_EQ(sim.carts.size(), 17);

  auto result = sim.find_first_crash();
  EXPECT_EQ(result.x, 115);
  EXPECT_EQ(result.y, 138);
  EXPECT_EQ(sim.carts.size(), 15);
}

TEST(MinecartMadnessTest, solvePart2){
  std::vector<std::string> board = utils::slurp_file_lines("day-13/input.txt");

  MinecartMadness::MinecartSimulation sim(board);
  auto result = sim.find_last_cart();
  EXPECT_EQ(sim.carts.size(), 1);
  EXPECT_EQ(result.x, 0);
  EXPECT_EQ(result.y, 98);
}
