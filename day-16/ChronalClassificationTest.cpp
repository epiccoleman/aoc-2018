#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "ChronalClassification.h"
#include "Opcodes.h"
using namespace ChronalClassification;

#include <algorithm>
using std::transform;

TEST(ChronalClassificationTest, canCheckIfOperationCouldHaveProvidedAGivenResult){
  Opcode opcode("inc",
                                       [](vector<int> v,
                                          __attribute__ ((unused)) vector<int>){
                                         transform(v.begin(), v.end(), v.begin(),
                                                   [](int i){ return ++i; });
                                         return v;
                                       });


  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 0, 0, 0 }; //irrelevant with this lambda
  vector<int> after_good { 2, 3, 4, 5 };

  vector<int> after_bad { 2, 1, 1, 2 };

  Instruction good { before, instruction, after_good };
  Instruction bad { before, instruction, after_bad };
  
  EXPECT_TRUE(opcode.validate(good));
  EXPECT_FALSE(opcode.validate(bad));
}

// TEST(ChronalClassificationTest, canCountPossibleOpcodes){
  
// }

// TEST(ChronalClassificationTest, canCountPossibleOpcodes){
  
// }

