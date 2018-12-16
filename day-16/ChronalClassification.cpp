#include "ChronalClassification.h"

ChronalClassification::Opcode::Opcode(string n, Operation op)
  : name(n),
    operation(op)
{}

bool ChronalClassification::Opcode::validate(Instruction instruction) {
  return instruction.after == operation(instruction.before, instruction.instruction);
}
