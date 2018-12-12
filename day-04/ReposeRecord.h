#ifndef DAY_04
#define DAY_04

#include <string>
#include <vector>
#include <map>

class ReposeRecord {
public:
  void process_log_lines(std::vector<std::string> logs);
  void process_line(std::string log);
  int sleepiest_guard();
  int sleepiest_minute(int guard_id);
  std::pair<int, int> guard_with_favoritest_minute();


  static int guard_id_from_log(std::string log);
  static int minute_from_log(std::string log);

  int currentGuard;
  bool sleeping;
  int sleepStarted;
  std::map<int, std::vector<int> > guardSleeps; // { guardId : { minute: sleepcount}}
};

#endif
