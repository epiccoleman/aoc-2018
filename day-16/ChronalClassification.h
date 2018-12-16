#ifndef DAY_16
#define DAY_16

#include <string>
#include <vector>
#include <functional>

// alright, on this one i'm using 'using', sorry google
using std::string;
using std::vector;
using std::function;

namespace ChronalClassification {
  class Opcode {
  public:
    Opcode(string name, function<vector<int>(vector<int>)> op);
    function<vector<int>(vector<int>)> operation;
    bool validate(vector<int> before, vector<int> after);
  private:
    string name;
  };

}

#endif
