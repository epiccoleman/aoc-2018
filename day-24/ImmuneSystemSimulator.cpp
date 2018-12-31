#include "ImmuneSystemSimulator.h"
#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <iostream>

ImmuneSystemSimulator::DamageType ImmuneSystemSimulator::damage_type_from_str(string str) {
  //switch(str) {  // haha nope, this is c++ where everything sucks
  if (str == "fire") return DamageType::Fire;
  if (str == "slashing") return DamageType::Slashing;
  if (str == "radiation") return DamageType::Radiation;
  if (str == "bludgeoning") return DamageType::Bludgeoning;
  if (str == "cold") return DamageType::Cold;
  // if this gets passed something else, explode
}

bool ImmuneSystemSimulator::is_valid_damage_type(string str) {
  return
    str == "fire"        ||
    str == "slashing"    ||
    str == "radiation"   ||
    str == "bludgeoning" ||
    str == "cold";
}

vector<ImmuneSystemSimulator::DamageType> ImmuneSystemSimulator::find_types_for_stat(string stat, string str) {
  vector<DamageType> damage_types;

  int start = str.find(stat);
  int end = start;

  if (start != std::string::npos){
    end = str.find(";", start);
    if (end == std::string::npos){
      end = str.find(")", start);
    }

    auto raw_types = str.substr(start, (end - start));
    raw_types.erase(0, raw_types.find(" ") + 1);
    raw_types.erase(0, raw_types.find(" ") + 1);
    vector<string> damage_type_strs;

    boost::split(damage_type_strs, raw_types, boost::is_any_of("\\ ,\\,"));
    for ( auto dt : damage_type_strs){
      if (is_valid_damage_type(dt)) damage_types.push_back(damage_type_from_str(dt));
    }
  }
  return damage_types;
}


vector<ImmuneSystemSimulator::DamageType> ImmuneSystemSimulator::weaknesses_from_str(string str) {
  return find_types_for_stat("weak", str);
}

vector<ImmuneSystemSimulator::DamageType> ImmuneSystemSimulator::immunities_from_str(string str) {
  return find_types_for_stat("immune", str);
}

// Unit
ImmuneSystemSimulator::Unit::Unit( int hit_points, int initiative, int attack_power, DamageType damage_type, vector<DamageType> weaknesses, vector<DamageType> immunities)
  :  hit_points(hit_points),
     initiative(initiative),
     attack_power(attack_power),
     damage_type(damage_type),
     weaknesses(weaknesses),
     immunities(immunities)
{}

// UnitGroup
ImmuneSystemSimulator::UnitGroup::UnitGroup(int unit_count, Unit unit_type)
  : unit_count(unit_count),
    unit_type(unit_type)
{}

ImmuneSystemSimulator::UnitGroup ImmuneSystemSimulator::UnitGroup::parse(string input) { //woof
  //split it up
  vector<string> words;
  boost::split(words, input, boost::is_any_of(" "));

  // parse all the stuff that is in known locations
  int hit_points = stoi(words[4]);
  int initiative = stoi(words.back());
  int attack_power = stoi(words[words.size() - 6]);
  DamageType damage_type = damage_type_from_str(words[words.size() - 5]);

  vector<DamageType> weaknesses = weaknesses_from_str(input);
  vector<DamageType> immunities = immunities_from_str(input);


  Unit unit(hit_points, initiative, attack_power, damage_type, weaknesses, immunities);


  int unit_count = stoi(words[0]);
  UnitGroup ug(unit_count, unit);
  ug.unit_count = unit_count;

  return ug;
}
