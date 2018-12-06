#ifndef DAY_03
#define DAY_03

#include <set>
#include <string>
#include <utility>

class FabricClaims {

public:
  FabricClaims(int i, int x, int y, int w, int h);
  static FabricClaims parse_claim(std::string input);
  
  int id;
  std::pair<int, int> top_left;
  int width;
  int height;
  std::set<std::pair<int, int> > points;

};

#endif
