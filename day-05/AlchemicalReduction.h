#ifndef DAY_05
#define DAY_05

#include <string>

namespace AlchemicalReduction {

  std::string react(std::string polymer);
  bool reactable(std::string polymer);
  std::string filter_unit(std::string polymer, char unit);
  int shortest_polymer(std::string polymer);

}

#endif
