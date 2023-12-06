#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {

  long int total_time{0};
  long int record{0};
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line[0] == 'T') {
      std::vector<std::string> words;
      boost::split(words, line, boost::is_any_of(": "),
                   boost::token_compress_on);
      std::string temp{""};
      for (auto i : words) {
        if (i != "Time") {
          temp += i;
        }
      }
      total_time = stol(temp);
    } else if (line[0] == 'D') {
      std::vector<std::string> words;
      boost::split(words, line, boost::is_any_of(": "),
                   boost::token_compress_on);
      std::string temp{""};
      for (auto i : words) {
        if (i != "Distance") {
          temp += i;
        }
      }
      record = stol(temp);
    } else {
      break;
    }
  }

  long int ways_to_beat{0};
  for (int hold = 0; hold < total_time; hold++) {
    long int run_time = total_time - hold;
    long int velocity = hold;
    long int distance_travelled{run_time * velocity};
    if (distance_travelled > record) {
      ways_to_beat += 1;
    }
  }
  std::cout << "Number of ways : " << ways_to_beat << std::endl;

  return 0;
}

