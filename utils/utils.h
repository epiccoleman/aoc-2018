#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace utils {
  std::vector<std::string> slurp_file_lines(std::string file_name);

  std::vector<std::string> slurp_file_tokens(std::string file_name);
  std::vector<int> slurp_file_as_ints(std::string file_name);

  void present_result(std::string text, int result);
  void present_result(std::string text, std::string result);

  int sum_factors(int n);
}

#endif
