#ifndef DAY_16
#define DAY_16

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <functional>

// alright, on this one i'm using 'using', sorry google
using std::string;
using std::vector;
using std::map;
using std::unordered_set;
using std::function;

namespace ChronalClassification {
  struct Instruction {
    vector<int> before;
    vector<int> instruction;
    vector<int> after;

    int opcode() { return instruction[0]; }
  };

  class Opcode {
  public:
    typedef function<vector<int>(vector<int>, vector<int>)> Operation;
    Opcode(string name, Operation op);
    bool validate(Instruction instruction) const;
    string name;
    Operation operation;
    // bool operator==(const Opcode& other);
  };

  class OpcodeClassifier {
  public:
    OpcodeClassifier(vector<Opcode> ops, vector<int> input)
      : opcodes(ops) { parse_input(input); deduce_opcode_ids(); }

    vector<Instruction> instructions;
    vector<Opcode> opcodes;

    void parse_input(vector<int> input);
    int count_possible_opcodes(Instruction instruction);
    int count_samples_with_three_possible_opcodes(); // too on the nose? 
    void deduce_opcode_ids();

  };


}

#endif
