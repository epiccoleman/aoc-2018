#ifndef DAY_21
#define DAY_21

#include "../day-19/Elfcode.h"

namespace Elfcode {
  class AnalyzingInterpreter : public ElfcodeInterpreter {
    void execute_program(std::vector<std::string> program) override;
  };

}

#endif
