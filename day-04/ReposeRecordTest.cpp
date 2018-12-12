#include <gtest/gtest.h>
#include "../utils/utils.h"

#include "ReposeRecord.h"

TEST(ReposeRecordTest, canPullMinuteFromLogLine){
  std::string test1 = "[1518-03-31 00:55] falls asleep";
  std::string test2 = "[1518-07-05 23:56] Guard #2593 begins shift";
  std::string test3 = "[1518-06-20 00:17] falls asleep";

  EXPECT_EQ(ReposeRecord::minute_from_log(test1), 55);
  EXPECT_EQ(ReposeRecord::minute_from_log(test2), 56);
  EXPECT_EQ(ReposeRecord::minute_from_log(test3), 17);
}

TEST(ResposeRecordTest, guardIdFromLog){
  std::string guard_str = "[1518-07-05 23:56] Guard #2593 begins shift";

  EXPECT_EQ(ReposeRecord::guard_id_from_log(guard_str), 2593);
}

TEST(ReposeRecordTest, whenLogLineIsShiftBeginCurrentGuardIsSet){
  std::string test2 = "[1518-07-05 23:56] Guard #2593 begins shift";

  ReposeRecord test;

  test.process_line(test2);
  
  EXPECT_EQ(test.currentGuard, 2593);
}

TEST(ReposeRecordTest, sleepiestGuard){
  std::vector<std::string> logs {
      "[1518-11-01 00:00] Guard #10 begins shift",
      "[1518-11-01 00:05] falls asleep",
      "[1518-11-01 00:25] wakes up",
      "[1518-11-01 00:30] falls asleep",
      "[1518-11-01 00:55] wakes up",
      "[1518-11-01 23:58] Guard #99 begins shift",
      "[1518-11-02 00:40] falls asleep",
      "[1518-11-02 00:50] wakes up",
      "[1518-11-03 00:05] Guard #10 begins shift",
      "[1518-11-03 00:24] falls asleep",
      "[1518-11-03 00:29] wakes up",
      "[1518-11-04 00:02] Guard #99 begins shift",
      "[1518-11-04 00:36] falls asleep",
      "[1518-11-04 00:46] wakes up",
      "[1518-11-05 00:03] Guard #99 begins shift",
      "[1518-11-05 00:45] falls asleep",
        "[1518-11-05 00:55] wakes up"};

  ReposeRecord test;
  test.process_log_lines(logs);

  EXPECT_EQ(test.sleepiest_guard(), 10);
}

TEST(ReposeRecordTest, sleepiestMinute){
  std::vector<std::string> logs {
    "[1518-11-01 00:00] Guard #10 begins shift",
      "[1518-11-01 00:05] falls asleep",
      "[1518-11-01 00:25] wakes up",
      "[1518-11-01 00:30] falls asleep",
      "[1518-11-01 00:55] wakes up",
      "[1518-11-01 23:58] Guard #99 begins shift",
      "[1518-11-02 00:40] falls asleep",
      "[1518-11-02 00:50] wakes up",
      "[1518-11-03 00:05] Guard #10 begins shift",
      "[1518-11-03 00:24] falls asleep",
      "[1518-11-03 00:29] wakes up",
      "[1518-11-04 00:02] Guard #99 begins shift",
      "[1518-11-04 00:36] falls asleep",
      "[1518-11-04 00:46] wakes up",
      "[1518-11-05 00:03] Guard #99 begins shift",
      "[1518-11-05 00:45] falls asleep",
      "[1518-11-05 00:55] wakes up"};

  ReposeRecord test;
  test.process_log_lines(logs);
  int sleepy_guy = test.sleepiest_guard();

  EXPECT_EQ(test.sleepiest_minute(sleepy_guy), 24);
}

TEST(ReposeRecordTest, solvePart1){
  std::vector<std::string> logs = utils::slurp_file_lines("day-04/input.txt");

  ReposeRecord test;
  test.process_log_lines(logs);

  int sleepy = test.sleepiest_guard();
  int minute = test.sleepiest_minute(sleepy);

  int result = sleepy * minute;
  utils::present_result("Part 1: ", result);

  EXPECT_EQ(result, 35623);
}

TEST(ReposeRecordTest, solvePart2){
  std::vector<std::string> logs = utils::slurp_file_lines("day-04/input.txt");

  ReposeRecord test;
  test.process_log_lines(logs);

  std::pair<int, int> result_pair = test.guard_with_favoritest_minute();

  int result = result_pair.first * result_pair.second;
  utils::present_result("Part 2: ", result);

  EXPECT_EQ(result, 23037);
}
