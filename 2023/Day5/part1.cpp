#include <boost/algorithm/string.hpp>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  // hash table to store seed numbers then soil numbers and so on
  std::unordered_map<int, long int> map;

  // checks whether a number is already converted as per the current rule
  std::unordered_map<int, int> check;

  // string to take each line of input in
  std::string sentence;

  // take input from console
  while (std::getline(std::cin, sentence)) {

    // skipping empty lines
    if (sentence == " " || sentence == "") {
      continue;
    }

    // filling the seeds in the hash table map
    else if (sentence.find("seeds:") != std::string::npos) {
      // split the sentence into parts with empty space " " as delimiter
      // store the parts into the vector 'words'
      std::vector<std::string> words;

      boost::split(words, sentence, boost::is_any_of(" "),
                   boost::token_compress_on);

      // convert strings to numbers and store in the hash table 'map'
      // also make corresponding entry in the 'check'
      int j{0};
      for (auto i : words) {
        if (i != "seeds:") {
          map.insert({j, stol(i)});
          check.insert({j, 0});
          j++;
        }
      }
    }

    // check for conversion rule lables ex- "seed-to-soil map:" etc.
    // reset the 'check' hash table
    else if (sentence[sentence.length() - 1] == ':') {
      for (auto &pair : check) {
        pair.second = 0;
      }
    }

    // for line containing numbers
    else {
      // split the sentence into parts and store in vector 'words'
      std::vector<std::string> words;
      boost::split(words, sentence, boost::is_any_of(" "),
                   boost::token_compress_on);

      // convert strings to numbers and store in another vector 'numbers'
      std::vector<long int> numbers;
      for (auto i : words) {
        numbers.push_back(stol(i));
      }

      // check if any value in the map lies in the range provided
      // and replace the value with the calculated destination value
      for (auto &pair : map) {
        if (check[pair.first] == 0 && pair.second >= numbers[1] &&
            pair.second < (numbers[1] + numbers[2])) {
          check[pair.first] = 1;
          pair.second = numbers[0] + pair.second - numbers[1];
        }
      }
    }
  }

  // Ctrl + D/Z to abort input

  // calculate and print out the minimum value (solution)
  long int minimum{map[0]};
  for (const auto &pair : map) {
    if (pair.second < minimum) {
      minimum = pair.second;
    }
  }
  std::cout << "Minimum : " << minimum << std::endl;

  return 0;
}

