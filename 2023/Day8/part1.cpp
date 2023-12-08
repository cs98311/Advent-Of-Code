#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
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

  std::string current{"AAA"};
  int steps{0};
  for (size_t i = 0; i < directions.size(); i = (i + 1) % directions.size()) {
    if (directions[i] == 'L') {
      current = lefts[current];
      steps += 1;
    } else {
      current = rights[current];
      steps += 1;
    }
    if (current == "ZZZ") {
      break;
    }
  }

  std::cout << "Number of steps : " << steps << std::endl;

  return 0;
}

