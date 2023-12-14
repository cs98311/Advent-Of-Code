#include <iostream>
#include <string>
#include <unordered_map>
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

  // total number of cycles
  unsigned long int num{1000000000};
  // last cycle to iterate
  unsigned long int last{num};

  // stores each state as a string
  std::unordered_map<std::string, unsigned long int> map;

  // initial state
  std::string ref_str;
  for (auto i = 0U; i < matrix.size(); i++) {
    for (auto j = 0U; j < matrix.size(); j++) {
      ref_str += (matrix[i][j]);
    }
  }
  map.insert({ref_str, -1});
  std::cout << ref_str << std::endl;

  // BEGIN CYCLES
  for (auto cycle = 0UL; cycle < last; cycle++) {
    //   NORTH
    for (auto j = 0U; j < matrix.size(); j++) {
      unsigned int last_dot{0};
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
          last_dot++;
        }
      }
    }

    // WEST
    for (auto i = 0U; i < matrix.size(); i++) {
      unsigned int last_dot{0};
      unsigned int dot_set{0};
      for (auto j = 0U; j < matrix.size(); j++) {
        if (matrix[i][j] == '.' && dot_set == 0) {
          last_dot = j;
          dot_set = 1;
        } else if (matrix[i][j] == '#') {
          dot_set = 0;
        } else if (matrix[i][j] == 'O' && dot_set == 1 && last_dot < j) {
          matrix[i][last_dot] = 'O';
          matrix[i][j] = '.';
          last_dot++;
        }
      }
    }

    //   SOUTH
    unsigned int matrix_size = static_cast<unsigned int>(matrix.size());
    for (unsigned int j = 0; j < matrix_size; j++) {
      unsigned int last_dot{matrix_size - 1};
      unsigned int dot_set{0};
      for (unsigned i = matrix_size; i-- > 0;) {
        if (matrix[i][j] == '.' && dot_set == 0) {
          last_dot = i;
          dot_set = 1;
        } else if (matrix[i][j] == '#') {
          dot_set = 0;

        } else if (matrix[i][j] == 'O' && dot_set == 1 && last_dot > i) {
          matrix[last_dot][j] = 'O';
          matrix[i][j] = '.';
          last_dot--;
        }
      }
    }

    // EAST
    for (auto i = 0U; i < matrix_size; i++) {
      unsigned int last_dot{matrix_size - 1};
      unsigned int dot_set{0};
      for (unsigned j = matrix_size; j-- > 0;) {
        if (matrix[i][j] == '.' && dot_set == 0) {
          last_dot = j;
          dot_set = 1;
        } else if (matrix[i][j] == '#') {
          dot_set = 0;

        } else if (matrix[i][j] == 'O' && dot_set == 1 && last_dot > j) {
          matrix[i][last_dot] = 'O';
          matrix[i][j] = '.';
          last_dot--;
        }
      }
    }

    // Check state string at end of each cycle
    std::string check_str;
    for (auto i = 0U; i < matrix.size(); i++) {
      for (auto j = 0U; j < matrix.size(); j++) {
        check_str += (matrix[i][j]);
      }
    }
    // search in the map and modify the last cycle
    if (map.count(check_str) > 0) {
      last = cycle + (num - cycle) % (cycle - map[check_str]);
    } else {
      map.insert({check_str, cycle});
    }
  }

  std::cout << "Total load : " << load << std::endl;

  return 0;
}

