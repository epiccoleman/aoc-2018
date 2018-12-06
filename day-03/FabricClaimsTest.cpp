#include <gtest/gtest.h>
#include "../utils/utils.h"
#include "FabricClaims.h"
#include <set>
#include <utility>

TEST(FabricClaimsTest, input_line_to_claim){
  std::string input = "#123 @ 3,2: 5x4";

  FabricClaims claim = FabricClaims::parse_claim(input);

  EXPECT_EQ(claim.id, 123);
  EXPECT_EQ(claim.top_left, std::pair(3, 2));
  EXPECT_EQ(claim.width, 5);
  EXPECT_EQ(claim.height, 4);
}

TEST(FabricClaimsTest, fabricClaimHasASetOfItsPointsUponConstruction){
  FabricClaims claim(123, 0, 0, 2, 2);

  std::set<std::pair<int, int> > expected_points { std::pair(0, 0),
                                                   std::pair(0, 1),
                                                   std::pair(1, 0),
                                                   std::pair(1, 1) };
  EXPECT_EQ(claim.points, expected_points);
}
