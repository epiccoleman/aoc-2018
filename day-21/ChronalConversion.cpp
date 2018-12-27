#include "ChronalConversion.h"

void execute_program(std::vector<std::string> program) {
  int max = 10000000;
  int i = 0;
  while(ip_value < program.size() && i < max){
    execute_instruction(program[ip_value]);
    i++;
    if (i % 100000 == 0) std::cerr << "Cycle " << i << std::endl;
  }
}
