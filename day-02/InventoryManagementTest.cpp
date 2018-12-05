#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "../utils/utils.h"

#include "InventoryManagement.h"

TEST(InventoryManagementTest, containsNOccurencesIsTrueForExactlyNOccurences){
  std::string test_id = "aaabbbccc";

  EXPECT_TRUE(InventoryManagement::contains_n_occurences(3, test_id));
  EXPECT_FALSE(InventoryManagement::contains_n_occurences(2, test_id));
}

TEST(InventoryManagementTest, multipleOccurrenceChecksCanBeTrue){
  std::string test_id = "aabbbcccc";

  EXPECT_TRUE(InventoryManagement::contains_n_occurences(2, test_id));
  EXPECT_TRUE(InventoryManagement::contains_n_occurences(3, test_id));
  EXPECT_TRUE(InventoryManagement::contains_n_occurences(4, test_id));
}

TEST(InventoryManagementTest, inventory_checksum){
  std::vector<std::string> ids { "abcdef", "bababc", "abbcde", "abcccd",
                                     "aabcdd", "abcdee", "ababab" };

  EXPECT_EQ(InventoryManagement::inventory_checksum(ids), 12);
}

TEST(InventoryManagementTest, count_differences){
  std::string a = "fghij";
  std::string b = "fguij";
  std::string c = "buttz";
  std::string d = "buttz";

  EXPECT_EQ(InventoryManagement::count_differences(a, b), 1);
  EXPECT_EQ(InventoryManagement::count_differences(b, c), 5);
  EXPECT_EQ(InventoryManagement::count_differences(c, d), 0);
}

TEST(InventoryManagementTest, common_letters){
  std::string a = "fghij";
  std::string b = "fguij";

  EXPECT_EQ(InventoryManagement::common_letters(a, b), "fgij");
}

TEST(InventoryManagementTest, find_similar_boxes_difference){
  std::vector<std::string> ids {"abcde", "fghij", "klmno", "pqrst",
                                "fguij", "axcye", "wvxyz" };
  EXPECT_EQ(InventoryManagement::find_similar_boxes_difference(ids), "fgij");
}

TEST(InventoryManagementTest, solvePart1){
  std::vector<std::string> ids = utils::slurp_file_as_strings("day-02/input.txt");

  int result = InventoryManagement::inventory_checksum(ids);

  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 7533);
}

TEST(InventoryManagementTest, solvePart2){
  std::vector<std::string> ids = utils::slurp_file_as_strings("day-02/input.txt");

  std::string result = InventoryManagement::find_similar_boxes_difference(ids);

  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, "mphcuasvrnjzzkbgdtqeoylva");
}
