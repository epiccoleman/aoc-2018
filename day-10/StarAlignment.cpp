#include "StarAlignment.h"

#include <algorithm>
#include <iostream>

#include "../utils/utils.h"

StarAlignment::Star::Star(utils::Point p, utils::Point v)
  : position(p),
    velocity(v)
{}

StarAlignment::Star::Star(int p_x, int p_y, int v_x, int v_y)
  : position {p_x, p_y},
    velocity {v_x, v_y}
{}

void StarAlignment::Star::advance_position() {
  position += velocity;
}

bool StarAlignment::possible_hit(std::vector<Star> stars, int time) {
  Star min_x = *std::min_element(stars.begin(), stars.end(),
                                 [](Star a, Star b){ return a.position.x < b.position.x; });

  Star max_x = *std::max_element(stars.begin(), stars.end(),
                                 [](Star a, Star b){ return a.position.x < b.position.x; });

  if (abs(max_x.position.x - min_x.position.x) > 100) return false;

  auto y_comp = [](Star a, Star b){ return a.position.y < b.position.y; };

  Star min_y = *std::min_element(stars.begin(), stars.end(), y_comp);

  Star max_y = *std::max_element(stars.begin(), stars.end(), y_comp);

  if (abs(max_y.position.y - min_y.position.y) > 10) return false;
  
  printf("hit at with range (%d,%d) (%d,%d)", min_x.position.x, min_y.position.y, max_x.position.x, max_y.position.y);
  printf("appeared at %d seconds", time);

  std::cout << std::endl;
  std::cout << "=================================================================" << std::endl;
  std::cout << std::endl;

    for(int j = min_y.position.y; j <= max_y.position.y; j ++){
      for(int i = min_x.position.x; i <= max_x.position.x; i++){
      if(std::find_if(stars.begin(), stars.end(), [i, j](Star star){ return star.position.x == i && star.position.y == j;}) != stars.end()){
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "=================================================================" << std::endl;
  std::cout << std::endl;

  std::cout << std::endl;

  return true;
}

void StarAlignment::advance_stars(std::vector<Star>& stars) {
  std::for_each(stars.begin(), stars.end(), [](Star& star){ star.advance_position(); });
}

std::vector<StarAlignment::Star> StarAlignment::slurp_input(){
  std::vector<std::string>  tokens = utils::slurp_file_tokens("day-10/input.txt");
  std::vector<int> nums(tokens.size());
  std::transform(tokens.begin(), tokens.end(), nums.begin(), [](std::string token){ return stoi(token);});

  std::vector<Star> stars;

  for(int i = 0; i < nums.size(); i += 4){

    stars.push_back(Star(nums[i], nums[i + 1], nums[i + 2], nums[i + 3]));
  }

  return stars;
}
