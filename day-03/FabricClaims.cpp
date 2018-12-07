#include "FabricClaims.h"
#include <algorithm> 
#include <iostream>
#include <map>

FabricClaims::FabricClaim::FabricClaim(int i, int x, int y, int w, int h)
  : id(i),
    top_left{x, y},
    width(w),
    height(h)
{
  for (int i = x; i < x + w; i++){
    for (int j = y; j < y + h; j++){
      points.insert(std::pair(i, j));
    }
  }
}

FabricClaims::FabricClaim FabricClaims::parse_claim(std::string input){
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

  next_delimiter = s.find('x'); int w = stoi(s.substr(0, next_delimiter)); s.erase(0, next_delimiter + 1);
  int h = stoi(s);

  return FabricClaim(id, x, y, w, h);
}

std::set<std::pair<int,int> > FabricClaims::contested_points(std::vector<FabricClaim> claims) {
  std::set<std::pair<int, int> > claimed_points;
  std::set<std::pair<int, int> > contested_points;

  for (FabricClaim claim : claims){
    for(std::pair<int, int> point : claim.points){
      if (!claimed_points.insert(point).second) {
        contested_points.insert(point);
      }
    }
  }

  return contested_points;
}

int FabricClaims::count_contested_points(std::vector<FabricClaim> claims){
  auto contested = contested_points(claims);
  return contested.size();
}


int FabricClaims::find_uncontested_claim(std::vector<FabricClaim> claims) {
  auto contested = contested_points(claims);

  for (FabricClaim claim : claims){
    std::vector<std::pair<int, int> > output_holder;
    std::set_intersection(contested.begin(), contested.end(), claim.points.begin(), claim.points.end(), std::back_inserter(output_holder));

    if(!output_holder.size()){
      return claim.id;
    }

  }

  return -1;
}
