#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/integer/common_factor.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {};

int main() {

  std::unordered_map<std::string, std::string> lefts;
  std::unordered_map<std::string, std::string> rights;

  std::vector<char> directions;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "" || line == " ") {
      break;
    }
    for (auto i : line) {
      directions.push_back(i);
    }
  }

  while (std::getline(std::cin, line)) {
    if (line == "" || line == " ") {
      break;
    }
    std::vector<std::string> words;
    boost::split(words, line, boost::is_any_of("=(), "),
                 boost::token_compress_on);
    lefts.insert({words[0], words[1]});
    rights.insert({words[0], words[2]});
  }

  // int max_steps{0};
  std::vector<long int> list_of_steps;
  // std::unordered_map<std::string, int> visited;
  std::string current;
  for (const auto &a : lefts) {
    if (a.first[2] == 'A') {

      int steps{0};
      current = a.first;
      for (size_t i = 0; i < directions.size();
           i = (i + 1) % directions.size()) {
        if (directions[i] == 'L') {
          current = lefts[current];
          steps += 1;
        } else {
          current = rights[current];
          steps += 1;
        }
        if (current[2] == 'Z') {
          break;
        }
      }
      list_of_steps.push_back(steps);
      // if (steps > max_steps && steps % max_steps == 0){

      // }
    } else {
      continue;
    }
  }

  long int llcm{list_of_steps[0]};
  for (size_t i = 0; i < list_of_steps.size(); i++) {
    if (i == list_of_steps.size() - 1) {
      break;
    } else {
      llcm = boost::integer::lcm(llcm, list_of_steps[i + 1]);
    }
  }

  std::cout << "Number of steps : " << llcm << std::endl;

  return 0;
}

