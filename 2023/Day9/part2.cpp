#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  long int total_sum{0};

  std::string line;

  while (std::getline(std::cin, line)) {

    if (line == " " || line == "") {
      break;
    }
    std::vector<std::vector<long int>> bigvec;

    std::vector<std::string> words;
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);

    std::vector<long int> sequence;

    // reverse enter the numbers
    for (auto i = words.size(); i-- > 0;) {
      sequence.push_back(stol(words[i]));
    }

    bigvec.push_back(sequence);

    auto row{0UL};

    long int sum{sequence[sequence.size() - 1]};
    while (1) {
      std::vector<long int> temp;
      for (auto i = 0UL; i < bigvec[row].size() - 1; i++) {
        temp.push_back(bigvec[row][i + 1] - bigvec[row][i]);
      }
      bigvec.push_back(temp);
      sum += temp[temp.size() - 1];
      if (temp[0] == 0 && temp[temp.size() - 1] == 0) {
        break;
      }
      row++;
    }

    total_sum += sum;
  }

  std::cout << "Total sum : " << total_sum << std::endl;

  return 0;
}
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  long int total_sum{0};

  std::string line;

  while (std::getline(std::cin, line)) {

    if (line == " " || line == "") {
      break;
    }
    std::vector<std::vector<long int>> bigvec;

    std::vector<std::string> words;
    boost::split(words, line, boost::is_any_of(" "), boost::token_compress_on);

    std::vector<long int> sequence;

    // reverse enter the numbers
    for (auto i = words.size(); i-- > 0;) {
      sequence.push_back(stol(words[i]));
    }

    bigvec.push_back(sequence);

    auto row{0UL};

    long int sum{sequence[sequence.size() - 1]};
    while (1) {
      std::vector<long int> temp;
      for (auto i = 0UL; i < bigvec[row].size() - 1; i++) {
        temp.push_back(bigvec[row][i + 1] - bigvec[row][i]);
      }
      bigvec.push_back(temp);
      sum += temp[temp.size() - 1];
      if (temp[0] == 0 && temp[temp.size() - 1] == 0) {
        break;
      }
      row++;
    }

    total_sum += sum;
  }

  std::cout << "Total sum : " << total_sum << std::endl;

  return 0;
}

