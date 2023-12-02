#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <regex>
#include <string>

int main() {

  std::string sentence;
  std::vector<std::string> words;
  int power_sum{0};

  while (std::getline(std::cin, sentence)) {

    int number{0};
    std::string color;
    int min_red{0};
    int min_green{0};
    int min_blue{0};
    int power{0};

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
      } else {
        color = i;
        if (color == "red" && number > min_red) {
          min_red = number;
        } else if (color == "green" && number > min_green) {
          min_green = number;
        } else if (color == "blue" && number > min_blue) {
          min_blue = number;
        }
      }
    }
    power = min_red * min_blue * min_green;
    power_sum += power;
    std::cout << "Current Power Sum : " << power_sum << '\n';
  }

  return 0;
}

