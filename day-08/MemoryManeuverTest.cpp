#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "MemoryManeuver.h"

TEST(MemoryManeuverTest, canParseSimpleList){
  std::list<int> test_list { 0, 2, 1, 3 };

  MemoryManeuver::memory_node test_node = MemoryManeuver::parse_input_from_list(test_list);

  EXPECT_EQ(test_node.children_count, 0);
  EXPECT_EQ(test_node.metadata_count, 2);
  EXPECT_TRUE(test_node.children.empty());
  EXPECT_EQ(test_node.metadata.size(), 2);
  EXPECT_EQ(test_node.metadata[0], 1);
  EXPECT_EQ(test_node.metadata[1], 3);
}

TEST(MemoryManeuverTest, parseMoreComplexList){
  std::list<int> test_list { 2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2 };

  MemoryManeuver::memory_node test_node = MemoryManeuver::parse_input_from_list(test_list);

  // A
  EXPECT_EQ(test_node.children.size(), 2);
  EXPECT_EQ(test_node.metadata.size(), 3);
  EXPECT_EQ(test_node.metadata[0], 1);
  EXPECT_EQ(test_node.metadata[1], 1);
  EXPECT_EQ(test_node.metadata[2], 2);

  // B
  EXPECT_EQ(test_node.children[0].children.size(), 0);
  EXPECT_EQ(test_node.children[0].metadata.size(), 3);
  EXPECT_EQ(test_node.children[0].metadata[0], 10);
  EXPECT_EQ(test_node.children[0].metadata[1], 11);
  EXPECT_EQ(test_node.children[0].metadata[2], 12);

  // C
  EXPECT_EQ(test_node.children[1].children.size(), 1);
  EXPECT_EQ(test_node.children[1].metadata.size(), 1);
  EXPECT_EQ(test_node.children[1].metadata[0], 2);

  // D
  EXPECT_EQ(test_node.children[1].children[0].children.size(), 0);
  EXPECT_EQ(test_node.children[1].children[0].metadata.size(), 1);
  EXPECT_EQ(test_node.children[1].children[0].metadata[0], 99);
}

TEST(MemoryManeuverTest, sum_metadataTest){
  std::list<int> test_list { 2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2 };

  MemoryManeuver::memory_node test_node = MemoryManeuver::parse_input_from_list(test_list);

  EXPECT_EQ(MemoryManeuver::sum_metadata(test_node), 138);
}

TEST(MemoryManeuverTest, whenNodeHasNoChildrennode_valueReturnsSumOfMetadata){
  MemoryManeuver::memory_node test_node;
  std::vector<int> test_metadata { 4, 8, 15, 16, 23, 42 };
  test_node.metadata = test_metadata;

  EXPECT_EQ(MemoryManeuver::node_value(test_node), 108);
}

TEST(MemoryManeuverTest, whenNodeHasChildrennode_valueReturnsSumOfNodeValuesReferencedByMetadata){
  std::list<int> test_list { 2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2 };

  MemoryManeuver::memory_node test_node = MemoryManeuver::parse_input_from_list(test_list);

  EXPECT_EQ(MemoryManeuver::node_value(test_node), 66);
}

TEST(MemoryManeuverTest, solvePart1){
  std::vector<int> input_v = utils::slurp_file_as_ints("day-08/input.txt");
  std::list<int> input;

  std::copy(input_v.begin(), input_v.end(), std::back_inserter(input));

  MemoryManeuver::memory_node test_node = MemoryManeuver::parse_input_from_list(input);

  int result = MemoryManeuver::sum_metadata(test_node);

  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 42951);
}

TEST(MemoryManeuverTest, solvePart2){
  std::vector<int> input_v = utils::slurp_file_as_ints("day-08/input.txt");
  std::list<int> input;

  std::copy(input_v.begin(), input_v.end(), std::back_inserter(input));

  MemoryManeuver::memory_node test_node = MemoryManeuver::parse_input_from_list(input);

  int result = MemoryManeuver::node_value(test_node);

  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, 18568);
}
