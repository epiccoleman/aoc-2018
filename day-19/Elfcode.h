#ifndef DAY_19
#define DAY_19

// #include "../day-16/ChronalClassification.h" //knew i'd regret that
#include <functional>
#include <vector>
#include <string>
#include <map>

namespace Elfcode {
  using Operation = std::function<std::vector<int>(std::vector<int>, std::vector<int>)>;
  struct Instruction {
    Instruction(Operation op, std::vector<int> args)
      : operation(op),
        arguments(args)
    {}
    Operation operation;
    std::vector<int> arguments;
  };

  class ElfcodeInterpreter {
  public:
    ElfcodeInterpreter(std::map<std::string, Operation> code_map, int ip_reg);

    virtual void execute_program(std::vector<std::string> program);
    void execute_instruction(const std::string& input);

    static const std::string instruction_name(const std::string& input);
    static const std::vector<int> instruction_args(std::string input);

    int ip_value;
    int ip_register;
    std::map<std::string, Operation> opcodes;
    std::vector<int> registers;
  };

}

#endif
