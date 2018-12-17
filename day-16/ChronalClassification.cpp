#include "ChronalClassification.h" 

#include <algorithm>
using std::count_if;

ChronalClassification::Opcode::Opcode(string n, Operation op)
  : name(n),
    operation(op)
{}

bool ChronalClassification::Opcode::validate(Instruction instruction) {
  return instruction.after == operation(instruction.before, instruction.instruction);
}

void ChronalClassification::OpcodeClassifier::parse_input(vector<int> input) {
  for(int i = 0; i < input.size(); i += 12){
    instructions.push_back(
      Instruction{
        { input[i], input[i+1], input[i+2], input[i+3]},
        { input[i+4], input[i+5], input[i+6], input[i+7]},
        { input[i+8], input[i+9], input[i+10], input[i+11]}
      });
  }
}

int ChronalClassification::OpcodeClassifier::count_possible_opcodes(Instruction instruction) {
  return count_if(opcodes.begin(),
                  opcodes.end(),
                  [instruction](Opcode opcode){
                    return opcode.validate(instruction);
                  });
}

int ChronalClassification::OpcodeClassifier::count_samples_with_three_possible_opcodes() {
  return count_if(instructions.begin(),
                  instructions.end(),
                  [this](Instruction instruction){
                    return this->count_possible_opcodes(instruction) >= 3;
                  });
}
