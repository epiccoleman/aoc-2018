#include "FabricClaims.h"
#include <iostream>

FabricClaims::FabricClaims(int i, int x, int y, int w, int h)
  : id(i),
    top_left{x, y},
    width(w),
    height(h)
{
  for (int i = x; i < x + w; i++){
    for (int j = y; j < y + h; j++){
      std::cerr << "inserting" << i << "," << j << std::endl;
      points.insert(std::pair(i, j));
    }
  }
}

FabricClaims FabricClaims::parse_claim(std::string input){
  std::string s = input;

  int next_delimiter = s.find(' ');
  int id = stoi(s.substr(1, next_delimiter));
  s.erase(0, s.find('@') + 2);

  next_delimiter = s.find(',');
  int x = stoi(s.substr(0, next_delimiter));
  s.erase(0, next_delimiter + 1);

  next_delimiter = s.find(':');
  int y = stoi(s.substr(0, next_delimiter));
  s.erase(0, next_delimiter + 1);

  next_delimiter = s.find('x');
  int w = stoi(s.substr(0, next_delimiter));
  s.erase(0, next_delimiter + 1);

  int h = stoi(s);

  return FabricClaims(id, x, y, w, h);
}
