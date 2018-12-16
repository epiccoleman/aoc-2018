#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "ChronalClassification.h"
using namespace ChronalClassification;

#include <algorithm>
using std::transform;

// TEST(ChronalClassificationTest, canConstructAnOpcodeWithALambda){
//   ChronalClassification::Opcode opcode("addi",
//                                        [](vector<int> input,
//                                           //jesus, c++
//                                           __attribute__ ((unused)) vector<int> instruction)
//                                        {
//                                          return input;
//                                        });

//   vector<int> reg { 1, 2, 3, 4 }; //because register is a non-functional reserved word in c++
//   vector<int> result = opcode.operation(reg);

//   EXPECT_EQ(result, reg);
// }

// TEST(ChronalClassificationTest, canCallOperationOnOpcode){
//   ChronalClassification::Opcode opcode("inc",
//                                        [](vector<int> v,
//                                           __attribute__ ((unused)) vector<int> x)
//                                        {
//                                          transform(v.begin(), v.end(), v.begin(),
//                                                    [](int i){ return ++i; });
//                                          return v;
//                                        });
//   vector<int> reg { 1, 2, 3, 4 };
//   vector<int> result = opcode.operation(reg);

//   vector<int> expected { 2, 3, 4, 5 };
//   EXPECT_EQ(result, expected);
// }

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

TEST(ChronalClassificationTest, ADDR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 1, 2, 1 };
  vector<int> after { 1, 5, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::ADDR;
  
  EXPECT_TRUE(opcode.validate(test));
}
