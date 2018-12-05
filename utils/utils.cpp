#include "utils.h"

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

std::vector<std::string> utils::slurp_file_as_strings(std::string file_name){
  std::ifstream input_file(file_name);
  std::istream_iterator<std::string> start(input_file), end;

  return std::vector<std::string>(start, end);
}

std::vector<int> utils::slurp_file_as_ints(std::string file_name){
  std::vector<std::string> input = slurp_file_as_strings(file_name);
  std::vector<int> numbers(input.size());

  std::transform(input.begin(), input.end(), numbers.begin(), [](std::string n) -> int { return stoi(n); });

  return numbers;
}

void utils::present_result(std::string text, int result){
  std::cerr << "==================================================" << std::endl;
  std::cerr << text << result << std::endl;
  std::cerr << "==================================================" << std::endl;
}

void utils::present_result(std::string text, std::string result){
  std::cerr << "==================================================" << std::endl;
  std::cerr << text << result << std::endl;
  std::cerr << "==================================================" << std::endl;
}
