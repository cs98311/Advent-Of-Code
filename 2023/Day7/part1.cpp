#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// gives each card of the hand a hexadecimal value
std::unordered_map<char, int> cards;

struct Hand {
  // strength of the hand
  int strength{0};
  // bid for the hand
  int bid{0};
  // hash table with card name as key and count as value
  std::unordered_map<char, int> hand_cards;
  // tie breakker for cards with same strength
  int tie_breaker{0};

  // Constructor
  Hand(std::string letters, int bid) : bid(bid), hand_cards() {
    unsigned int length = static_cast<unsigned int>(letters.length()) - 1;
    // convert hexadecimal 'letters' to decimal 'tie_breaker'
    for (unsigned int i = 0; i <= length; i++) {
      double power = 4 - i;
      // 16^0 * units + 16^1 * tens + 16^2 * hundreds + 16^3 * thousands + 16^4
      // * ten_thousands
      tie_breaker += cards[letters[i]] * static_cast<int>(pow(16, power));
      // Add the cards and count of cards in the hash map
      if (hand_cards.count(letters[i]) > 0) {
        hand_cards[letters[i]] += 1;
      } else {
        hand_cards.insert({letters[i], 1});
      }
    }

    // Calculate strength
    // 'K' : 5 or KKKKK
    if (hand_cards.size() == 1) {
      strength = 7;
    }
    // QKT54
    else if (hand_cards.size() == 5) {
      strength = 1;
    }
    // AA456
    else if (hand_cards.size() == 4) {
      strength = 2;
    }

    else if (hand_cards.size() == 2) {
      for (const auto &pair : hand_cards) {
        // KKKK66
        if (pair.second == 4 || pair.second == 1) {
          strength = 6;
          break;
        }
        // KKKK12
        else {
          strength = 5;
          break;
        }
      }
    } else {
      for (const auto &pair : hand_cards) {
        // AABBC
        if (pair.second == 2) {
          strength = 3;
          break;
        }
        // ABBBC
        else if (pair.second == 3) {
          strength = 4;
          break;
        } else {
          continue;
        }
      }
    }
  }
};

// function to sort a vector of vectors by index1 first and ayn equal values by
// index2
void multi_index_sort_vector(std::vector<std::vector<int>> *vec, size_t index1,
                             size_t index2) {
  std::sort(
      vec->begin(), vec->end(),
      [index1, index2](const std::vector<int> &a, const std::vector<int> &b) {
        return (a[index1] < b[index1]) ||
               ((a[index1] == b[index1]) && (a[index2] < b[index2]));
      });
}

int main() {

  cards.insert({'2', 2});
  cards.insert({'3', 3});
  cards.insert({'4', 4});
  cards.insert({'5', 5});
  cards.insert({'6', 6});
  cards.insert({'7', 7});
  cards.insert({'8', 8});
  cards.insert({'9', 9});
  cards.insert({'T', 10});
  cards.insert({'J', 11});
  cards.insert({'Q', 12});
  cards.insert({'K', 13});
  cards.insert({'A', 14});

  // {{strength, tie breaker, bid},.....}
  std::vector<std::vector<int>> ranks;

  // string to store input inside
  std::string line;

  while (std::getline(std::cin, line)) {
    // abort input if empty string
    if (line == "" || line == " ") {
      break;
    } else {
      // split the input into 2 strings and store in vector 'words'
      std::vector<std::string> words;
      boost::split(words, line, boost::is_any_of(" "),
                   boost::token_compress_on);
      // Create an instance of Hand struct and pass the input
      Hand hand(words[0], stoi(words[1]));
      // temporary vector to push the modified strength and bid to the 'ranks'
      // matrix
      std::vector<int> temp;
      temp.push_back(hand.strength);
      temp.push_back(hand.tie_breaker);
      temp.push_back(hand.bid);
      ranks.push_back(temp);
    }
  }

  // sort the matrix acc to strength then tie breaker in ascending order
  multi_index_sort_vector(&ranks, 0, 1);

  // rank is index+1 since ascending order
  unsigned long int total_winnings{0};
  for (size_t i = 0; i < ranks.size(); i++) {
    total_winnings += static_cast<unsigned int>(ranks[i][2]) * (i + 1);
  }
  std::cout << "Total winnings : " << total_winnings << std::endl;

  return 0;
}

