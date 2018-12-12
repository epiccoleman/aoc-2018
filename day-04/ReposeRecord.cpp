#include "ReposeRecord.h"
#include <algorithm>
#include <utility>

void ReposeRecord::process_log_lines(std::vector<std::string> logs) {
  std::for_each(logs.begin(), logs.end(),
                [this](std::string log){ process_line(log); } );
}

void ReposeRecord::process_line(std::string log) {

  if(log.find("Guard") != std::string::npos){
    currentGuard = guard_id_from_log(log);
  }
  else if(!sleeping){
    sleeping = true;
    sleepStarted = minute_from_log(log);
  }
  else if(sleeping) {
    sleeping = false;

    int current_time = minute_from_log(log);

    for(int i = sleepStarted; i < current_time; i++){
      guardSleeps[currentGuard].push_back(i);
    }
  }
}

int ReposeRecord::sleepiest_guard() {
  auto guard_it =  std::max_element(guardSleeps.begin(), guardSleeps.end(),
                                    [this](std::pair<int, std::vector<int> > guard_a,
                                           std::pair<int, std::vector<int> > guard_b){
                                      return guard_a.second.size() < guard_b.second.size();
    });

  return guard_it->first;
}

int ReposeRecord::sleepiest_minute(int guard_id) {
  std::vector<int> sleep_record = guardSleeps.find(guard_id)->second;

  std::map<int, int> minute_records;

  for(auto i : sleep_record){
    minute_records[i]++;  // holy shit, something concise!
  }

  auto minute_it = std::max_element(minute_records.begin(), minute_records.end(),
                                    [this](std::pair<int, int> minute_a,
                                           std::pair<int, int> minute_b){
                                      return minute_a.second < minute_b.second;
                                    });

  return minute_it->first;
}

std::pair<int, int> ReposeRecord::guard_with_favoritest_minute(){
  std::map<int, std::pair<int, int> > all_minute_records;

  for (auto guard : guardSleeps){
    std::vector<int> sleep_record = guard.second;

    std::map<int, int> minute_records;

    for(auto i : sleep_record){
      minute_records[i]++;  // holy shit, something concise!
    }

    auto minute_it = std::max_element(minute_records.begin(), minute_records.end(),
                                      [this](std::pair<int, int> minute_a,
                                             std::pair<int, int> minute_b){
                                        return minute_a.second < minute_b.second;
                                      });

    all_minute_records[guard.first] = *minute_it;
  }

  auto guard_it = std::max_element(all_minute_records.begin(), all_minute_records.end(),
                                    [this](std::pair<int, std::pair<int, int> > guard_record_a,
                                           std::pair<int, std::pair<int, int> > guard_record_b){
                                      return guard_record_a.second.second < guard_record_b.second.second; 
                                    });

  return { guard_it->first, guard_it->second.first};


}

int ReposeRecord::guard_id_from_log(std::string log) {
  log.erase(0, log.find('#') + 1);
  log.erase(log.find(' '), log.size());
  return stoi(log);
}

int ReposeRecord::minute_from_log(std::string log){
  return stoi(log.substr(15, 2));
}

