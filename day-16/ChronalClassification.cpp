#include "ChronalClassification.h"

ChronalClassification::Opcode::Opcode(string n, function<vector<int>(vector<int>)> op)
  : name(n),
    operation(op)
{}

bool ChronalClassification::Opcode::validate(vector<int> before, vector<int> after) {
  return after == operation(before);
}
