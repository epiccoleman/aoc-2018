#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "ImmuneSystemSimulator.h"

using namespace ImmuneSystemSimulator;

TEST(ImmuneSystemSimulatorTest, damage_type_from_str){
  EXPECT_EQ(damage_type_from_str("fire"), DamageType::Fire);
  EXPECT_EQ(damage_type_from_str("slashing"), DamageType::Slashing);
  EXPECT_EQ(damage_type_from_str("radiation"), DamageType::Radiation);
  EXPECT_EQ(damage_type_from_str("bludgeoning"), DamageType::Bludgeoning);
  EXPECT_EQ(damage_type_from_str("cold"), DamageType::Cold);
}

TEST(ImmuneSystemSimulatorTest, is_valid_damage_type){
  EXPECT_TRUE(is_valid_damage_type("fire"));
  EXPECT_TRUE(is_valid_damage_type("slashing"));
  EXPECT_TRUE(is_valid_damage_type("radiation"));
  EXPECT_TRUE(is_valid_damage_type("bludgeoning"));
  EXPECT_TRUE(is_valid_damage_type("cold"));
  EXPECT_FALSE(is_valid_damage_type("farts"));
}

TEST(ImmuneSystemSimulatorTest, weaknesses_from_str){
  string input = "18 units each with 729 hit points (weak to fire; immune to cold, slashing) with an attack that does 8 radiation damage at initiative 10";
  vector<DamageType> expected { DamageType::Fire };

  EXPECT_EQ(weaknesses_from_str(input), expected);
}

TEST(ImmuneSystemSimulatorTest, immunities_from_str){
  string input = "18 units each with 729 hit points (weak to fire; immune to cold, slashing) with an attack that does 8 radiation damage at initiative 10";
  vector<DamageType> expected { DamageType::Cold, DamageType::Slashing };

  EXPECT_EQ(immunities_from_str(input), expected);
}

TEST(ImmuneSystemSimulatorTest, canParseAUnitGroupFromInputString){
  string input = "18 units each with 729 hit points (weak to fire; immune to cold, slashing) with an attack that does 8 radiation damage at initiative 10";

  auto ug = UnitGroup::parse(input);

  EXPECT_EQ(ug.unit_count, 18);
  EXPECT_EQ(ug.unit_type.hit_points, 729);
  EXPECT_EQ(ug.unit_type.initiative, 10);
  EXPECT_EQ(ug.unit_type.attack_power, 8);
  EXPECT_EQ(ug.unit_type.damage_type, DamageType::Radiation);
  EXPECT_EQ(ug.unit_type.weaknesses.size(), 1);
  EXPECT_EQ(ug.unit_type.weaknesses[0], DamageType::Fire);
  EXPECT_EQ(ug.unit_type.immunities.size(), 2);
  EXPECT_EQ(ug.unit_type.immunities[0], DamageType::Cold);
  EXPECT_EQ(ug.unit_type.immunities[1], DamageType::Slashing);
}
