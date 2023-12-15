#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  std::ifstream in;
  in.open("input.txt");

  std::ofstream out;
  out.open("out2.txt");
  assert(out.is_open());

  int total{0};
  std::string line;

  if (in.is_open()) {
    while (!in.eof()) {
      std::getline(in, line);

      if (line == "") {
        std::clog << "Newline encountered!" << std::endl;
        break;
      } else if (line == " ") {
        std::clog << "Empty string encountered!" << std::endl;
        break;
      }
      std::vector<std::string> words;
      boost::split(words, line, boost::is_any_of(","));
      for (auto i : words) {
        int current_value{0};
        for (auto j : i) {
          current_value += static_cast<int>(j);
          current_value *= 17;
          current_value %= 256;
        }
        total += current_value;
      }
    }
  } else {
    std::clog << "file not open\n";
  }

  out << "Total sum : " << total << std::endl;
  out.close();
  in.close();

  return 0;
}

