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

TEST(ChronalClassificationTest, canCountPossibleOpcodes){
  vector<int> testInput { 3, 2, 1, 1, 9, 2, 1, 2, 3, 2, 2, 1 };

  OpcodeClassifier test(Opcodes::OPCODES, testInput);

  EXPECT_EQ(test.count_possible_opcodes(test.instructions[0]), 3);
}

TEST(ChronalClassificationTest, parseInput){
  vector<int> testInput { 3, 2, 1, 1, 9, 2, 1, 2, 3, 2, 2, 1 };

  OpcodeClassifier test(Opcodes::OPCODES, testInput);

  vector<int> expected_before { 3, 2, 1, 1 };
  vector<int> expected_instruction { 9, 2, 1, 2 };
  vector<int> expected_after { 3, 2, 2, 1 };

  EXPECT_EQ(test.instructions[0].before, expected_before);
  EXPECT_EQ(test.instructions[0].instruction, expected_instruction);
  EXPECT_EQ(test.instructions[0].after, expected_after);
}

TEST(ChronalClassificationTest, solvePart1){
  vector<int> testInput = utils::slurp_file_as_ints("day-16/input-part-1.txt");

  OpcodeClassifier test(Opcodes::OPCODES, testInput);

  int result = test.count_samples_with_three_possible_opcodes();

  utils::present_result("Part 1: ", result);
  EXPECT_EQ(result, 509);
}

