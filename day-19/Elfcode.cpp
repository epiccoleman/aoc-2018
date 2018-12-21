#include "Elfcode.h"
#include <iostream>
#include <sstream>
#include <iterator>

Elfcode::ElfcodeInterpreter::ElfcodeInterpreter(std::map<std::string, Operation> code_map, int ip_reg)
  : ip_value(0),
    ip_register(ip_reg), // gets set when evaluating a program
    opcodes(code_map),
    registers { 0, 0, 0, 0, 0, 0 }
{}


void Elfcode::ElfcodeInterpreter::execute_instruction(const std::string& input) {
  registers[ip_register] = ip_value;

  // std::cerr << "Instruction: " << input << std::endl;
  auto op = instruction_name(input);
  auto args = instruction_args(input);
  registers = opcodes[op](registers, args);
  ip_value = registers[ip_register];
  ip_value++;
  // std::cerr << "Registers: { ";
  // fprintf(stderr, "%4d, %10d, %10d, %4d, %4d, %4d", registers[0], registers[1],registers[2],registers[3],registers[4],registers[5]);
  // std::cerr << " }" << std::endl;
}

void Elfcode::ElfcodeInterpreter::execute_program(std::vector<std::string> program) {
  int max = 10000000;
  int i = 0;
  while(ip_value < program.size() && i < max){
    execute_instruction(program[ip_value]);
    i++;
    if (i % 100000 == 0) std::cerr << "Cycle " << i << std::endl;
  }
}

const std::string Elfcode::ElfcodeInterpreter::instruction_name(const std::string& input) {
  return input.substr(0, input.find(' '));
}

const std::vector<int> Elfcode::ElfcodeInterpreter::instruction_args(std::string input) {
  std::vector<int> args;

  std::istringstream iss(input);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>());

  for (int i = 1; i < 4; i++){
    args.push_back(stoi(results[i]));
  }

  return args;
}

