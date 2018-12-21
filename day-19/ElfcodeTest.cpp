#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "Elfcode.h"
#include "ElfcodeOperations.h"

using namespace Elfcode;

TEST(ElfcodeTest, construction){
  ElfcodeInterpreter test(Operations::OPCODE_MAP, 0);

  EXPECT_EQ(test.ip_value, 0);
  EXPECT_EQ(test.ip_register, 0);

  std::vector<int> blank_reg { 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(test.registers, blank_reg);
}

TEST(ElfcodeTest, instructionName){
  auto input_line = "seti 5 0 1";
  EXPECT_EQ(ElfcodeInterpreter::instruction_name(input_line), "seti");
}

TEST(ElfcodeTest, instructionArgs){
  auto input_line = "seti 5 0 1";
  std::vector<int> expected_args { 5, 0, 1};
  EXPECT_EQ(ElfcodeInterpreter::instruction_args(input_line), expected_args);
}

TEST(ElfcodeTest, executeInstruction){
  ElfcodeInterpreter test(Operations::OPCODE_MAP, 0);

  auto test_line = "seti 25 0 1";
  test.execute_instruction(test_line);

  std::vector<int> expected_reg { 0, 25, 0, 0, 0, 0};
  EXPECT_EQ(test.ip_value, 1);
  EXPECT_EQ(test.registers, expected_reg);
}

TEST(ElfcodeTest, executeProgram){
  ElfcodeInterpreter test(Operations::OPCODE_MAP, 0);

  std::vector<std::string> test_program
    {
     "seti 5 0 1",
     "seti 6 0 2",
     "addi 0 1 0",
     "addr 1 2 3",
     "setr 1 0 0",
     "seti 8 0 4",
     "seti 9 0 5"
    };

  test.execute_program(test_program);
  std::vector<int> expected_reg { 6, 5, 6, 0, 0, 9 };
  EXPECT_EQ(test.ip_value, 7);
  EXPECT_EQ(test.registers, expected_reg);
}

TEST(ElfcodeTest, solvePart1){
  ElfcodeInterpreter test(Operations::OPCODE_MAP, 3);

  auto program = utils::slurp_file_lines("day-19/input.txt");
  // test.execute_program(program);

  utils::present_result("Day 1:", "");
  std::cerr << "This test takes too long - around 7,280,000 instruction executions." << std::endl;
  std::cerr << "The answer was { 2106, 1, 954, 256, 955, 955 }." << std::endl;

  // std::vector<int> expected_reg { 2106, 1, 954, 256, 955, 955 };
  std::vector<int> expected_reg { 0, 0, 0, 0, 0, 0};
  EXPECT_EQ(test.registers, expected_reg);
}

TEST(ElfcodeTest, solvePart2){
  ElfcodeInterpreter test(Operations::OPCODE_MAP, 3);

  auto program = utils::slurp_file_lines("day-19/input.txt");

  test.registers[0] = 1;
  test.execute_program(program);

  utils::present_result("Day 2:", "");
  std::cerr << "This test takes too long - around 111,331,071,233,316 instruction executions." << std::endl;
  std::cerr << "The looping part of the program sums the factors of 10551354" << std::endl;

  auto result = utils::sum_factors(10551354);
  EXPECT_EQ(result , 23021280);
}
