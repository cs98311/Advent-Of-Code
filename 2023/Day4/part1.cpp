#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  // string to contain 1 card's content at a time
  std::string sentence;

  // total worth of cards (solution)
  int total_worth{0};

  // read 1 card at a time into a string from console input
  while (std::getline(std::cin, sentence)) {
    // vector to holds parts of the string
    std::vector<std::string> words;
    // individual card's worth
    int card_worth{0};
    // hash table to store the winning numbers
    std::unordered_map<int, int> winning_nos;
    // hash table to store the numbers we have
    std::unordered_map<int, int> my_nos;
    // pointer that points to our hash tables
    std::unordered_map<int, int> *hold{nullptr};
    // split the sentence into parts with empty space " " as delimiter
    // store the parts into the vector 'words'
    boost::split(words, sentence, boost::is_any_of(" "),
                 boost::token_compress_on);
    // iterate over the vector
    for (auto i : words) {
      // skip if the element is the word "Card"
      if (i == "Card") {
        continue;
      }
      // Point to the winning numbers vector
      // if the last character is ":" ex- 1:, 12:, 134:
      else if (i[i.length() - 1] == ':') {
        hold = &winning_nos;
      }
      // Point to the my_nos vector
      // if the element is "|"
      else if (i == "|") {
        hold = &my_nos;
      }
      // check if the element is a single digit number
      else if (isdigit(i[0]) && i.length() == 1) {
        // insert the number as a key in the hash table
        // value doesn't matter so inserted 1
        // '5' - '0' turns it into integer 5
        // i[0] and not i since i is a string
        hold->insert(std::make_pair(i[0] - '0', 1));
      }
      // check if the element is a double digit number
      // but not 1: etc (already checked above)
      else if (isdigit(i[0]) && i.length() == 2 && i[i.length() - 1] != ':') {
        // multiply tens digit by 10 and units digit by 1 then add
        hold->insert(std::make_pair(10 * (i[0] - '0') + (i[1] - '0'), 1));
      }
    }

    // iterate over winning numbers hash table
    for (const auto &pair : winning_nos) {
      // check if found in my_nos keys
      if (my_nos.count(pair.first) > 0) {
        // for first number found
        if (card_worth == 0) {
          card_worth += 1;
        }
        // for subsequent numbers found
        else {
          card_worth *= 2;
        }
      }
    }
    // add card's worth to the total worth
    total_worth += card_worth;
  }

  // print the total worth
  std::cout << "Total worth : " << total_worth << std::endl;

  return 0;
}

