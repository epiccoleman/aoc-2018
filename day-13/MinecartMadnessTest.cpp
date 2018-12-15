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
