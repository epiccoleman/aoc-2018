#include <gtest/gtest.h>
#include "Point.h"

TEST(PointTest, canInstantiatePoint){
  utils::Point test { 42, 2112 };
  EXPECT_EQ(test.x, 42);
  EXPECT_EQ(test.y, 2112);
}

TEST(PointTest, canAddPoints){
  utils::Point testA { 42, 42 };
  utils::Point testB { 42, -42 };
  utils::Point result = testA + testB;

  EXPECT_EQ(result.x, 84);
  EXPECT_EQ(result.y, 0);
}

TEST(PointTest, canUsePlusEqualsOperator){
  utils::Point testA { 42, 42 };
  utils::Point testB { 42, -42 };
  testA += testB;

  EXPECT_EQ(testA.x, 84);
  EXPECT_EQ(testA.y, 0);
}

TEST(PointTest, equalityOperator){
  utils::Point testA { 42, 42 };
  utils::Point testB { 42, 42 };

  EXPECT_EQ(testA, testB);
}
