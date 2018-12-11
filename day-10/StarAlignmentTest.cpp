#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "StarAlignment.h"
#include "iostream"

TEST(StarAlignmentTest, advance_position){

  utils::Point test{ 2, 2 };

  StarAlignment::Star star(test, test);
  star.advance_position();

  EXPECT_EQ(star.position.x, 4);
  EXPECT_EQ(star.position.y, 4);
}

TEST(StarAlignmentTest, advance_stars){
  std::vector<StarAlignment::Star> stars;

  stars.push_back(StarAlignment::Star(0, 0, 1, 1));
  stars.push_back(StarAlignment::Star(2, 2, -1, -1));

  StarAlignment::advance_stars(stars);

  EXPECT_EQ(stars[0].position.x, 1);
  EXPECT_EQ(stars[0].position.y, 1);
  EXPECT_EQ(stars[1].position.x, 1);
  EXPECT_EQ(stars[1].position.y, 1);
}

TEST(StarAlignmentTest, slurp_input){
  auto stars = StarAlignment::slurp_input();

  EXPECT_EQ(stars.size(), 362);
  EXPECT_EQ(stars[0].position.x, 20316);
  EXPECT_EQ(stars[0].position.y, -30055);
  EXPECT_EQ(stars[0].velocity.x, -2);
  EXPECT_EQ(stars[0].velocity.y, 3);
}

TEST(StarAlignmentTest, hits){
  auto stars = StarAlignment::slurp_input();

  int count = 0;
  for( int i = 1; i < 10077; i++){
    StarAlignment::advance_stars(stars);
    if(StarAlignment::possible_hit(stars, i)){
      ++count;
    }
  }

  EXPECT_EQ(count, 1);
}
