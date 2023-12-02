#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <regex>
#include <string>

int main() {

  int total{0};
  for (int i = 0; i < 101; i++) {
    total += i;
  }

  std::string sentence;
  std::vector<std::string> words;
  int id_sum{0};
  int red_max{12};
  int green_max{13};
  int blue_max{14};

  while (std::getline(std::cin, sentence)) {

    int id{0};
    int number{0};
    std::string color;

    boost::split(words, sentence, boost::is_any_of(":,;\t "),
                 boost::token_compress_on);
    for (auto i : words) {
      if (isdigit(i[0])) {
        if (isdigit(i[2])) {
          number = (i[0] - '0') * 100 + (i[1] - '0') * 10 + (i[2] - '0');
        } else if (isdigit(i[1])) {
          number = (i[0] - '0') * 10 + (i[1] - '0');
        } else {
          number = i[0] - '0';
        }
        if (color == "Game") {
          id = number;
          color = "noGame";
        }
      } else {
        color = i;
        if (color == "red" && number > red_max) {
          id_sum += id;
          break;
        } else if (color == "green" && number > green_max) {
          id_sum += id;
          break;
        } else if (color == "blue" && number > blue_max) {
          id_sum += id;
          break;
        }
      }
    }
    std::cout << "Current ID Sum : " << total - id_sum << '\n';
  }

  return 0;
}

