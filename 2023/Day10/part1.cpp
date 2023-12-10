#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  std::vector<std::vector<char>> matrix;
  std::string line;

  // starting row and column
  unsigned int rs{0};
  unsigned int cs{0};
  unsigned int row{0};

  while (std::getline(std::cin, line)) {
    if (line == " " || line == "") {
      row++;
      break;
    }

    unsigned int column{0};
    std::vector<char> words;
    for (auto i : line) {
      words.push_back(i);
      if (i == 'S') {
        rs = row;
        cs = column;
      }
      column++;
    }
    matrix.push_back(words);

    row++;
  }

  int steps{0};
  char symbol;

  // current row and column
  unsigned int r{rs};
  unsigned int c{cs + 1};
  // starting direction
  std::string dirn{"right"};

  while (1) {
    if (r == rs && c == cs) {
      break;
    }

    symbol = matrix[r][c];

    if (symbol == '-') {
      if (dirn == "right") {
        c++;
      } else if (dirn == "left") {
        c--;
      }
    }

    else if (symbol == 'J') {
      if (dirn == "right") {
        r--;
        dirn = "up";
      } else if (dirn == "down") {
        c--;
        dirn = "left";
      }
    }

    else if (symbol == '|') {
      if (dirn == "up") {
        r--;
      } else if (dirn == "down") {
        r++;
      }
    }

    else if (symbol == '7') {
      if (dirn == "up") {
        c--;
        dirn = "left";
      } else if (dirn == "right") {
        r++;
        dirn = "down";
      }
    }

    else if (symbol == 'F') {
      if (dirn == "left") {
        r++;
        dirn = "down";
      } else if (dirn == "up") {
        c++;
        dirn = "right";
      }
    }

    else if (symbol == 'L') {
      if (dirn == "left") {
        r--;
        dirn = "up";
      } else if (dirn == "down") {
        c++;
        dirn = "right";
      }
    }
    steps++;
  }

  std::cout << "Steps : " << (steps + 1) / 2 << std::endl;

  return 0;
}

