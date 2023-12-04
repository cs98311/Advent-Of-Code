#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  // string to contain 1 card's content at a time
  std::string sentence;

  // card numbers as keys and no of their instances as values
  std::unordered_map<int, int> card_occurances;

  // variable to store card number
  int card_number{0};

  // read one card at a time into a string from console input
  while (std::getline(std::cin, sentence)) {
    // skip if empty string passed
    if (sentence == " " || sentence == "") {
      continue;
    }

    // vector to holds parts of the string
    std::vector<std::string> words;
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

    // Both hash tables for the current card are filled

    // current card's number
    card_number += 1;

    // create the key for current card if not already present
    if (card_occurances.count(card_number) == 0) {
      // insert the cardnumber as key and no. of occurances as value
      card_occurances.insert({card_number, 1});
    } else {
      // add 1 to value when card is visited for the original card
      card_occurances[card_number] += 1;
    }

    // number of matches found with winning numbers
    int no_of_matches{0};

    // iterate over winning numbers hash table of current card to find matches
    for (const auto &pair : winning_nos) {
      // check if found in my_nos keys
      if (my_nos.count(pair.first) > 0) {
        // increase the matches variable accordingly
        no_of_matches += 1;
      }
    }

    // add the value of current card to the values of next no_of_matches cards
    for (int i = 1; i <= no_of_matches; i++) {
      // create their keys if not already present
      if (card_occurances.count(card_number + i) == 0) {
        card_occurances.insert(std::make_pair(card_number + i, 0));
      }
      // add the value (no. of occurances) of current card to the value of
      // current+i card
      card_occurances[card_number + i] += card_occurances[card_number];
    }
  }

  // variable to store the total sum of values(no. of card occurances)
  int value_sum{0};
  for (const auto &pair : card_occurances) {
    // skip the extra keys created beyond the total number of cards
    // can't break due to ordering of hash table
    if (pair.first > card_number) {
      continue;
    }
    // add the values of cards_occurances hash table
    value_sum += pair.second;
  }

  // print the result
  std::cout << "Total Scratchcards : " << value_sum << std::endl;

  return 0;
}

