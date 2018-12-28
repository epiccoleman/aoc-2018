#ifndef DAY_24
#define DAY_24

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace ImmuneSystemSimulator {

  enum class DamageType
  {
   Fire, Slashing, Radiation, Bludgeoning, Cold
  };
  DamageType damage_type_from_str(string str);
  bool is_valid_damage_type(string str);
  vector<DamageType> find_types_for_stat(string stat, string str);
  vector<DamageType> weaknesses_from_str(string str);
  vector<DamageType> immunities_from_str(string str);

  class Unit {
  public:
    Unit(int hit_points, int initiative, int attack_power, DamageType damage_type, vector<DamageType> weaknesses, vector<DamageType> immunities);
    int hit_points;
    int initiative;
    int attack_power;
    DamageType damage_type;
    vector<DamageType> weaknesses;
    vector<DamageType> immunities;
  };

  class UnitGroup {
  public:
    static UnitGroup parse(string input);
    UnitGroup(int unit_count, Unit unit_type);
    int effective_power();
    int unit_count;
    Unit unit_type;
  };

  class Army {
  public:
    string name;

    vector<UnitGroup> unit_groups;
  };

  class Simulation {
  public:
    void step();

    Army immune_system_army;
    Army infection_army;
  };


}

#endif
