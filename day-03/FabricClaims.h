#ifndef DAY_03
#define DAY_03

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace FabricClaims {

  class FabricClaim {
  public:
    FabricClaim(int i, int x, int y, int w, int h);
    bool inside_claim(std::pair<int, int> point);
  
    int id;
    std::pair<int, int> top_left;
    int width;
    int height;
    std::set<std::pair<int, int> > points;
  };

  FabricClaim parse_claim(std::string input);
  int count_contested_points(std::vector<FabricClaim> claims);
}
#endif
