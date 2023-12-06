#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::vector<int> times;
  std::vector<int> records;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line[0] == 'T') {
      std::vector<std::string> words;
      boost::split(words, line, boost::is_any_of(" "),
                   boost::token_compress_on);
      for (auto i : words) {
        if (i != "Time:") {
          times.push_back(stoi(i));
        }
      }
    } else if (line[0] == 'D') {
      std::vector<std::string> words;
      boost::split(words, line, boost::is_any_of(" "),
                   boost::token_compress_on);
      for (auto i : words) {
        if (i != "Distance:") {
          records.push_back(stoi(i));
        }
      }
    } else {
      break;
    }
  }

  int solution{1};

  for (size_t i = 0; i < times.size(); i++) {
    int total_time{times[i]};
    int distance_to_beat{records[i]};
    int ways_to_beat{0};
    for (int hold = 0; hold < total_time; hold++) {
      int run_time = total_time - hold;
      int velocity = hold;
      int distance_travelled{run_time * velocity};
      if (distance_travelled > distance_to_beat) {
        ways_to_beat += 1;
      }
    }
    solution *= ways_to_beat;
  }

  std::cout << "Number of ways : " << solution << std::endl;

  return 0;
}

