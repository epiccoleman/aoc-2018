#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "Opcodes.h"
using namespace ChronalClassification;

TEST(OpcodesTest, ADDR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 1, 2, 1 };
  vector<int> after { 1, 5, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::ADDR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, ADDI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 1, 40, 3 };
  vector<int> after { 1, 2, 3, 42 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::ADDI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, MULR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 3, 2, 3 };
  vector<int> after { 1, 2, 3, 12 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::MULR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, MULI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 3, 2, 0 };
  vector<int> after { 8, 2, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::MULI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, BANR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 1, 2, 3 };
  vector<int> after { 1, 2, 3, 2 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::BANR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, BANI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 2, 7, 0 };
  vector<int> after { 3, 2, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::BANI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, BORR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 3, 1, 3 };
  vector<int> after { 1, 2, 3, 6 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::BORR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, BORI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 1, 5, 0 };
  vector<int> after { 7, 2, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::BORI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, SETR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 0, 1, 3 };
  vector<int> after { 1, 2, 3, 1 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::SETR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, SETI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 42, 5, 1 };
  vector<int> after { 1, 42, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::SETI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, GTIR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 4, 1, 3 };
  vector<int> after { 1, 2, 3, 1 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::GTIR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, GTRI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 3, 5, 1 };
  vector<int> after { 1, 0, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::GTRI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, GTRR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 3, 1, 1 };
  vector<int> after { 1, 1, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::GTRR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, EQIR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 0, 1, 2 };
  vector<int> after { 1, 2, 0, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::EQIR;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, EQRI){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 0, 1, 2 };
  vector<int> after { 1, 2, 1, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::EQRI;
  
  EXPECT_TRUE(opcode.validate(test));
}

TEST(OpcodesTest, EQRR){
  vector<int> before { 1, 2, 3, 4 };
  vector<int> instruction { 0, 3, 1, 1 };
  vector<int> after { 1, 0, 3, 4 };

  Instruction test { before, instruction, after };

  auto opcode = Opcodes::EQRR;
  
  EXPECT_TRUE(opcode.validate(test));
}
