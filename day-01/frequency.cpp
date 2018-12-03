#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>

using std::string;
using std::vector;

vector<string> slurp_file(string file_name){
  std::ifstream input_file(file_name);
  std::istream_iterator<string> start(input_file), end;

  return vector<string>(start, end);
}

int main(){
  vector<string> input = slurp_file("input.txt");
  vector<int> numbers(input.size());

  std::transform(input.begin(), input.end(), numbers.begin(), [](string n) -> int { return stoi(n); });

  int result = std::accumulate(numbers.begin(), numbers.end(), 0); 
  std::cout << result << std::endl;
}
