#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

struct Pattern {

  std::vector<std::string> *pattern;

  Pattern(std::vector<std::string> *matrix) : pattern(matrix) {}

  unsigned int check_columns() {
    // rotate the pattern and check again for mirror in rows
    std::vector<std::string> rotated;

    for (auto i = 0U; i < static_cast<unsigned int>(pattern->at(0).size());
         i++) {
      std::vector<char> temp;
      for (auto j = 0U; j < static_cast<unsigned int>(pattern->size()); j++) {
        temp.push_back(pattern->at(j)[i]);
      }
      std::string str;
      for (auto a : temp) {
        str.append(1, a);
      }
      rotated.push_back(str);
    }

    for (auto i = 0U; i < static_cast<unsigned int>(rotated.size() - 1); i++) {
      unsigned int row1{i};
      unsigned int row2{i + 1};
      while (rotated[row1] == rotated[row2]) {
        if (row2 == static_cast<unsigned int>(rotated.size() - 1) ||
            row1 == 0) {
          return i + 1;
        } else {
          row1--;
          row2++;
        }
      }
    }

    return 0;
  }

  // function to check for a mirror along rows
  unsigned int check_rows() {
    for (auto i = 0U; i < static_cast<unsigned int>(pattern->size() - 1); i++) {
      // variables that move in opposite direction starting from current row and
      // next row
      unsigned int row1{i};
      unsigned int row2{i + 1};
      // keep checking two rows for likeness till one end of pattern reached
      while (pattern->at(row1) == pattern->at(row2)) {
        // return if one of the matching rows in on the edge
        if (row2 == static_cast<unsigned int>(pattern->size() - 1) ||
            row1 == 0) {
          return i + 1;
        }
        //        [0]  <--row1--  [i][i+1]  --row2--> [length-1]
        else {
          row1--;
          row2++;
        }
      }
    }
    return 0;
  }
};

int main() {
  // final answer
  unsigned int sum{0};
  // list of all strings in a pattern
  std::vector<std::string> matrix;
  // take input line by line
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line == "" || line == " ") {
      // make a Pattern instance using the matrix
      Pattern p(&matrix);
      // check if a mirror found along rows
      unsigned int row_mirror{p.check_rows()};
      if (row_mirror) {
        sum += 100 * row_mirror;
      }
      // if not then check the columns
      else {
        unsigned int column_mirror{p.check_columns()};
        if (column_mirror) {
          sum += column_mirror;
        } else {
          std::clog << "Column mirror not found!" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      // Clear the matrix and restart the while loop
      matrix.clear();
    }
    // if not empty line, push into the matrix (vector of strings)
    else {
      matrix.push_back(line);
    }
  }

  // print the final result
  std::cout << "Sum : " << sum << std::endl;
  return 0;
}

