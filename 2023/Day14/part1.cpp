#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
int main() {

  unsigned int load{0};
  std::string line;
  std::vector<std::vector<char>> matrix;
  while (std::getline(std::cin, line)) {
    if (line == "" || line == " ") {
      break;
    }
    std::vector<char> temp;
    for (auto i : line) {
      temp.push_back(i);
    }
    matrix.push_back(temp);
  }
  // matrix filled
  for (auto j = 0U; j < matrix.size(); j++) {
    unsigned int last_dot{0};
    // set 0 if can't fill the last_dot and 1 if can fill
    unsigned int dot_set{0};
    for (auto i = 0U; i < matrix.size(); i++) {
      if (matrix[i][j] == '.' && dot_set == 0) {
        last_dot = i;
        dot_set = 1;
      } else if (matrix[i][j] == '#') {
        dot_set = 0;

      } else if (matrix[i][j] == 'O' && dot_set == 1 && last_dot < i) {
        matrix[last_dot][j] = 'O';
        matrix[i][j] = '.';

        load += static_cast<unsigned int>(matrix.size()) - last_dot;
        last_dot++;
      }
      // non-shifting O's
      else if (matrix[i][j] == 'O') {
        load += static_cast<unsigned int>(matrix.size()) - i;
      }
    }
  }

  std::cout << "Total load : " << load << std::endl;

  return 0;
}

