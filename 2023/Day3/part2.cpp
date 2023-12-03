#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// function to extract number given location of one digit in the matrix
unsigned long int extract_number(const std::vector<std::vector<char>> &matrix,
                                 unsigned long int i, unsigned long int j) {

  // triple digit cases
  // jNN
  if (isdigit(matrix[i][j + 1]) && isdigit(matrix[i][j + 2])) {
    return static_cast<unsigned long int>(100 * (matrix[i][j] - '0') +
                                          10 * (matrix[i][j + 1] - '0') +
                                          (matrix[i][j + 2] - '0'));
  }

  // NjN
  else if (isdigit(matrix[i][j - 1]) && isdigit(matrix[i][j + 1])) {
    return static_cast<unsigned long int>(100 * (matrix[i][j - 1] - '0') +
                                          10 * (matrix[i][j] - '0') +
                                          (matrix[i][j + 1] - '0'));
  }

  // NNj
  else if (isdigit(matrix[i][j - 1]) && isdigit(matrix[i][j - 2])) {
    return static_cast<unsigned long int>(100 * (matrix[i][j - 2] - '0') +
                                          10 * (matrix[i][j - 1] - '0') +
                                          (matrix[i][j] - '0'));
  }

  // double digit cases
  // Nj
  else if (isdigit(matrix[i][j - 1]) && !isdigit(matrix[i][j + 1]) &&
           !isdigit(matrix[i][j - 2])) {
    return static_cast<unsigned long int>((matrix[i][j] - '0') +
                                          10 * (matrix[i][j - 1] - '0'));
  }
  // jN
  else if (isdigit(matrix[i][j + 1]) && !isdigit(matrix[i][j - 1]) &&
           !isdigit(matrix[i][j + 2])) {
    return static_cast<unsigned long int>(10 * (matrix[i][j] - '0') +
                                          (matrix[i][j + 1] - '0'));
  }

  // single digit
  // j
  else if (!isdigit(matrix[i][j - 1]) && !isdigit(matrix[i][j + 1])) {
    return static_cast<unsigned long int>(matrix[i][j] - '0');
  }

  else {
    // return an int to prevent warning
    return 9999;
  }
}

int main() {

  // 2d matrix : vector of vectors of characters
  std::vector<std::vector<char>> matrix;

  // each row(vector) in the matrix
  std::string row_string;

  // total sum of powers (solution)
  unsigned long int sum{0};

  // filling the matrix from console input
  while (std::cin >> row_string) {
    std::vector<char> row_vector;
    for (auto ch : row_string) {
      row_vector.push_back(ch);
    }
    matrix.push_back(row_vector);
  }

  // Press Ctrl+D/Z to indicate end of input

  // length of a row (uniform)
  auto row_length{static_cast<unsigned long int>(matrix[0].size())};

  // string of symbols
  std::string symbols{"0123456789"};

  // access matrix rows
  for (auto i = 0UL; i < matrix.size(); i++) {
    // access characters in the row
    for (auto j = 0UL; j < row_length; j++) {
      // check if character is a *
      if (j > 0 && j < row_length - 1 && (matrix[i][j] == '*')) {
        // print i,j info for debugging
        // std::cout << "Gear : " << matrix[i][j] << " in i : " << i
        //           << ", j : " << j;

        // number of unique adjacent numbers
        unsigned long int adjacency{0};

        // power of this *
        unsigned long int power{1};

        // number extracted from string
        unsigned long int number{0};

        // hash table with the adjacent nnumbers as keys
        std::unordered_map<unsigned long int, unsigned long int> map;

        // check neighbours of * for numerical characters
        for (auto x = i - 1; x < i + 2; x++) {
          // take care of unsigned integer wrapping
          if (x > matrix.size() - 1) {
            continue;
          }
          for (auto y = j - 1; y < j + 2; y++) {
            // take care of unsigned integer wrapping
            if (y > row_length - 1) {
              continue;
            }
            // search for the character in the symbols(digits) string
            if (symbols.find(matrix[x][y]) != std::string::npos) {
              // extract the full number to which the digit belongs
              number = extract_number(matrix, x, y);
              // prevent duplicates obtained from different digits of the same
              // number
              if (map.count(number) == 0) {
                // increase the adjacency by 1 if not found
                adjacency += 1;
                // add the number to the hash table
                map.insert(std::make_pair(number, adjacency));
              }
            }
          }
        }

        // Check if adjacency equal to 2 as per the problem
        if (adjacency == 2) {
          // Calculate power for this *
          for (const auto &pair : map) {
            power *= pair.first;
            // std::cout << ", nums : " << pair.first;
          }
          //   std::cout << ", Power : " << power;
          // Add power to the total sum
          sum += power;
          //   std::cout << ", Current Sum : " << sum;
        }
        // std::cout << std::endl;
      }
    }
  }
  // Print the total sum of powers
  std::cout << "\nSum : " << sum << std::endl;

  return 0;
}

