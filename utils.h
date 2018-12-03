#include <fstream>
#include <vector>
#include <iterator>

using std::string;
using std::vector;

namespace utils {
  vector<string> slurp_file_as_strings(string file_name){
    std::ifstream input_file(file_name);
    std::istream_iterator<string> start(input_file), end;

    return vector<string>(start, end);
  }

  vector<int> slurp_file_as_ints(string file_name){
    vector<string> input = slurp_file_as_strings(file_name);
    vector<int> numbers(input.size());

    std::transform(input.begin(), input.end(), numbers.begin(), [](string n) -> int { return stoi(n); });

    return numbers;
  }
}
