#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>

#include "../utils.h"

using std::string;
using std::vector;

int main(){
  vector<int> numbers = utils::slurp_file_as_ints("input.txt");
  int result1 = std::accumulate(numbers.begin(), numbers.end(), 0); 
  std::cout << "Result 1: " result << std::endl;
}
