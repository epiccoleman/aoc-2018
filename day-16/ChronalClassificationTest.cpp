#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "ChronalClassification.h"

#include <algorithm>
using std::transform;

TEST(ChronalClassificationTest, canConstructAnOpcodeWithALambda){
  ChronalClassification::Opcode opcode("addi", [](vector<int> v){ return v; });

  vector<int> reg { 1, 2, 3, 4 }; //because register is a non-functional reserved word in c++
  vector<int> result = opcode.operation(reg);

  EXPECT_EQ(result, reg);
}

TEST(ChronalClassificationTest, canCallOperationOnOpcode){
  ChronalClassification::Opcode opcode("inc",
                                       [](vector<int> v){
                                         transform(v.begin(), v.end(), v.begin(),
                                                   [](int i){ return ++i; });
                                         return v;
                                       });
  vector<int> reg { 1, 2, 3, 4 };
  vector<int> result = opcode.operation(reg);

  vector<int> expected { 2, 3, 4, 5 };
  EXPECT_EQ(result, expected);
}

TEST(ChronalClassificationTest, canCheckIfOperationCouldHaveProvidedAGivenResult){
  ChronalClassification::Opcode opcode("inc",
                                       [](vector<int> v){
                                         transform(v.begin(), v.end(), v.begin(),
                                                   [](int i){ return ++i; });
                                         return v;
                                       });


  vector<int> before { 1, 2, 3, 4 };
  vector<int> after_good { 2, 3, 4, 5 };
  vector<int> after_bad { 2, 1, 1, 2 };

  EXPECT_TRUE(opcode.validate(before, after_good));
  EXPECT_FALSE(opcode.validate(before, after_bad));
}
