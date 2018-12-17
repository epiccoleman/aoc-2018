#ifndef DAY_16
#define DAY_16

#include <iostream>
#include <string>
#include <vector>
#include <functional>

// alright, on this one i'm using 'using', sorry google
using std::string;
using std::vector;
using std::function;

namespace ChronalClassification {
  struct Instruction {
    vector<int> before;
    vector<int> instruction;
    vector<int> after;
  };

  class Opcode {
  public:
    typedef function<vector<int>(vector<int>, vector<int>)> Operation;
    Opcode(string name, Operation op);
    bool validate(Instruction instruction);

  private:
    Operation operation;
    string name;
  };

  class OpcodeClassifier {
    vector<Instruction> instructions;
    vector<Opcode> opcodes;

    void parse_input(vector<string> input);
    int count_possible_opcodes(Instruction instruction);
  };


}

#endif
