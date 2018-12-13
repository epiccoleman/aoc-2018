#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "AlchemicalReduction.h"

TEST(AlchemicalReductionTest, reaction){
  std::string input = "dabAcCaCBAcCcaDA";

  EXPECT_EQ(AlchemicalReduction::react(input), "dabCBAcaDA");
}

TEST(AlchemicalReductionTest, reactable){
  std::string reactable1 = "Aa";
  std::string reactable2 = "dabAcCaCBAcCcaDA";
  std::string not_reactable1 = "dmb";
  std::string not_reactable2 = "dabCBAcaDA";

  EXPECT_TRUE(AlchemicalReduction::reactable(reactable1));
  EXPECT_TRUE(AlchemicalReduction::reactable(reactable2));
  EXPECT_FALSE(AlchemicalReduction::reactable(not_reactable1));
  EXPECT_FALSE(AlchemicalReduction::reactable(not_reactable2));
}

TEST(AlchemicalReductionTest, filter_unit){
  std::string test = "dabAcCaCBAcCcaDA";

  EXPECT_EQ(AlchemicalReduction::filter_unit(test, 'a'), "dbcCCBcCcD");
}

TEST(AlchemicalReductionTest, solvePart1){
  std::string input = utils::slurp_file_lines("day-05/input.txt")[0];

  std::string result = AlchemicalReduction::react(input);
  utils::present_result("Part 1: ", result.size());

  EXPECT_EQ(result.size(), 11310);
}

TEST(AlchemicalReductionTest, solvePart2){
  std::string input = utils::slurp_file_lines("day-05/input.txt")[0];

  int result = AlchemicalReduction::shortest_polymer(input);
  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, 6020);
}
