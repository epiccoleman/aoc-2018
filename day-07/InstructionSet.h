#ifndef DAY_07
#define DAY_07

#include <set>
#include <map>
#include <vector>
#include <string>

struct Instruction {
  Instruction() : completed(false), prerequisites{} {}
  std::set<char> prerequisites;
  bool completed;
};

class InstructionSet {
public:
  InstructionSet(const std::vector<std::string> rules);

  std::map<char, Instruction> instruction_set;
  std::set<char> available_instructions;

private:
  void add_rule(const std::string rule);
};

#endif
