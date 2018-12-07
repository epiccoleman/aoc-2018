#include <gtest/gtest.h>
#include "../utils/utils.h"
#include "FabricClaims.h"
#include <set>
#include <utility>

TEST(FabricClaimsTest, input_line_to_claim){
  std::string input = "#123 @ 3,2: 5x4";

  FabricClaims::FabricClaim claim = FabricClaims::parse_claim(input);

  EXPECT_EQ(claim.id, 123);
  EXPECT_EQ(claim.top_left, std::pair(3, 2));
  EXPECT_EQ(claim.width, 5);
  EXPECT_EQ(claim.height, 4);
}

TEST(FabricClaimsTest, fabricClaimHasASetOfItsPointsUponConstruction){
  FabricClaims::FabricClaim claim(123, 0, 0, 2, 2);

  std::set<std::pair<int, int> > expected_points { std::pair(0, 0),
                                                   std::pair(0, 1),
                                                   std::pair(1, 0),
                                                   std::pair(1, 1) };
  EXPECT_EQ(claim.points, expected_points);
}

TEST(FabricClaimsTest, countContestedPoints){
  std::vector<FabricClaims::FabricClaim> claims {
    FabricClaims::FabricClaim(123, 0, 0, 2, 2),
      FabricClaims::FabricClaim(223, 1, 1, 2, 2) };

  EXPECT_EQ(FabricClaims::count_contested_points(claims), 1);
}

TEST(FabricClaimsTest, solvePart1){
  std::vector<std::string> claim_strings = utils::slurp_file_lines("day-03/input.txt");

  std::vector<FabricClaims::FabricClaim> claims; //(claim_strings.size());

  for (auto claim_string : claim_strings) {
    claims.push_back(FabricClaims::parse_claim(claim_string));
  }

  int result = FabricClaims::count_contested_points(claims);

  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 112418);
}
