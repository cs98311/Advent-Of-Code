#include <iostream>
#include <regex>
#include <string>

int main() {

  int sum{0};
  int init{0};
  int end{0};

  std::string word;

  while (std::cin >> word) {

    std::cout << "Original Word : " << word << '\n';

    if (word.find("one") != std::string::npos) {
      word = std::regex_replace(word, std::regex("one"), "1");
    }

    if (word.find("two") != std::string::npos) {
      word = std::regex_replace(word, std::regex("two"), "2");
    }
    if (word.find("tw1") != std::string::npos) {
      word = std::regex_replace(word, std::regex("tw"), "2");
    }

    if (word.find("three") != std::string::npos) {
      word = std::regex_replace(word, std::regex("three"), "3");
    }

    if (word.find("four") != std::string::npos) {
      word = std::regex_replace(word, std::regex("four"), "4");
    }

    if (word.find("five") != std::string::npos) {
      word = std::regex_replace(word, std::regex("five"), "5");
    }

    if (word.find("six") != std::string::npos) {
      word = std::regex_replace(word, std::regex("six"), "6");
    }

    if (word.find("seven") != std::string::npos) {
      word = std::regex_replace(word, std::regex("seven"), "7");
    }

    if (word.find("eight") != std::string::npos) {
      word = std::regex_replace(word, std::regex("eight"), "8");
    }

    if (word.find("eigh2") != std::string::npos) {
      word = std::regex_replace(word, std::regex("eigh"), "8");
    }
    if (word.find("eigh3") != std::string::npos) {
      word = std::regex_replace(word, std::regex("eigh"), "8");
    }
    if (word.find("1ight") != std::string::npos) {
      word = std::regex_replace(word, std::regex("ight"), "8");
    }
    if (word.find("3ight") != std::string::npos) {
      word = std::regex_replace(word, std::regex("ight"), "8");
    }
    if (word.find("5ight") != std::string::npos) {
      word = std::regex_replace(word, std::regex("ight"), "8");
    }

    if (word.find("nine") != std::string::npos) {
      word = std::regex_replace(word, std::regex("nine"), "9");
    }
    if (word.find("7ine") != std::string::npos) {
      word = std::regex_replace(word, std::regex("ine"), "9");
    }
    if (word.find("nin8") != std::string::npos) {
      word = std::regex_replace(word, std::regex("nin"), "9");
    }

    std::cout << "Modified Word : " << word << '\n';

    int first{1};
    for (char ch : word) {
      if (isdigit(ch) && first) {
        init = ch - '0';
        end = ch - '0';
        first = 0;
      } else if (isdigit(ch)) {
        end = ch - '0';
      }
    }
    std::cout << "To add : " << init * 10 + end << '\n';
    sum += init * 10 + end;
    std::cout << "Current sum : " << sum << '\n';
  }

  return 0;
}
