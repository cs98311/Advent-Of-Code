#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

// original mirror row/column found
unsigned int org_row{100};
unsigned int org_col{100};

struct Pattern {

  std::vector<std::string> *pattern;

  Pattern(std::vector<std::string> *matrix) : pattern(matrix) {}

  unsigned int check_columns() {
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
      // skip checking the original mirror column if any
      if (i == org_col) {
        continue;
      }
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

    return 100;
  }

  unsigned int check_rows() {
    for (auto i = 0U; i < static_cast<unsigned int>(pattern->size() - 1); i++) {
      // skip checking the original mirror row if any
      if (i == org_row) {
        continue;
      }
      unsigned int row1{i};
      unsigned int row2{i + 1};
      while (pattern->at(row1) == pattern->at(row2)) {
        if (row2 == static_cast<unsigned int>(pattern->size() - 1) ||
            row1 == 0) {
          return i + 1;
        } else {
          row1--;
          row2++;
        }
      }
    }
    return 100;
  }
};

int main() {
  unsigned int sum{0};
  std::vector<std::string> matrix;
  std::string line;
  while (std::getline(std::cin, line)) {

    int while_exit{0};

    if (line == "" || line == " ") {
      // reset the global variables for this pattern
      org_row = 100;
      org_col = 100;

      // Get the original mirror row/column
      Pattern p_org(&matrix);
      unsigned int row_mirror_org{p_org.check_rows()};
      if (row_mirror_org != 100) {
        org_row = row_mirror_org - 1;
      } else {
        unsigned int column_mirror_org{p_org.check_columns()};
        if (column_mirror_org != 100) {
          org_col = column_mirror_org - 1;
        }
      }

      // Swap every character until the new mirror is found
      for (auto i = 0U; i < matrix.size(); i++) {
        for (auto j = 0U; j < matrix[0].size(); j++) {
          std::vector<std::string> new_matrix{matrix};
          if (new_matrix[i][j] == '.') {
            new_matrix[i][j] = '#';
          } else if (new_matrix[i][j] == '#') {
            new_matrix[i][j] = '.';
          }

          // operations
          Pattern p(&new_matrix);
          unsigned int row_mirror{p.check_rows()};
          if (row_mirror != 100) {
            sum += 100 * row_mirror;

            while_exit = 1;
            break;
          } else {
            unsigned int column_mirror{p.check_columns()};
            if (column_mirror != 100) {
              sum += column_mirror;
              while_exit = 1;
              break;
            } else {
              continue;
            }
          }
        }
        if (while_exit) {
          break;
        }
      }

      matrix.clear();
    } else {
      matrix.push_back(line);
    }
  }

  // Ctrl+D after entering last input

  std::cout << "Sum : " << sum << std::endl;
  return 0;
}

