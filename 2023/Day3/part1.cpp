#include <iostream>
#include <string>
#include <vector>

int main() {

  // 2d matrix (vector of vectors of characters)
  std::vector<std::vector<char>> matrix;

  // each row/vector in the matrix
  std::string row_string;

  // total sum
  int sum{0};

  // filling the matrix from console input
  while (std::cin >> row_string) {
    std::vector<char> row_vector;
    for (auto ch : row_string) {
      row_vector.push_back(ch);
    }
    matrix.push_back(row_vector);
  }

  // Press Ctrl+D/Z to end input

  // length of any row
  auto row_length{static_cast<unsigned long int>(matrix[0].size())};

  //   string of symbols
  std::string symbols{"!@#$%^&*()/-=+"};

  // access matrix rows
  for (auto i = 0UL; i < matrix.size(); i++) {
    // access characters of the row
    for (auto j = 0UL; j < row_length; j++) {
      // single digit number cases
      if (j > 0 && j < row_length - 1 && isdigit(matrix[i][j]) &&
          !isdigit(matrix[i][j + 1]) && !isdigit(matrix[i][j - 1])) {
        if (symbols.find(matrix[i][j + 1]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i][j - 1]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i + 1][j]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i + 1][j + 1]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i + 1][j - 1]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i - 1][j]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i - 1][j + 1]) != std::string::npos) {
          sum += matrix[i][j] - '0';

        } else if (symbols.find(matrix[i - 1][j - 1]) != std::string::npos) {
          sum += matrix[i][j] - '0';
        }
      }
      // double digit number cases
      else if (j > 0 && j < row_length - 2 && isdigit(matrix[i][j]) &&
               isdigit(matrix[i][j + 1]) && !isdigit(matrix[i][j - 1]) &&
               !isdigit(matrix[i][j + 2])) {

        if (symbols.find(matrix[i][j + 2]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (symbols.find(matrix[i][j - 1]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j + 1]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j + 2]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j - 1]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j + 1]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j + 2]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j - 1]) != std::string::npos) {
          sum += 10 * (matrix[i][j] - '0') + (matrix[i][j + 1] - '0');
        }
      }
      // triple digit number cases
      else if (j < row_length - 2 && isdigit(matrix[i][j]) &&
               isdigit(matrix[i][j + 1]) && isdigit(matrix[i][j + 2])) {

        if (j < row_length - 3 &&
            symbols.find(matrix[i][j + 3]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (symbols.find(matrix[i][j - 1]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        }

        else if (i < matrix.size() - 1 &&
                 symbols.find(matrix[i + 1][j]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j + 1]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j + 2]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (j < row_length - 3 && i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j + 3]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (i < matrix.size() - 1 &&
                   symbols.find(matrix[i + 1][j - 1]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        }

        else if (i > 0 && symbols.find(matrix[i - 1][j]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j + 1]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j + 2]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (j < row_length - 3 && i > 0 &&
                   symbols.find(matrix[i - 1][j + 3]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');

        } else if (i > 0 &&
                   symbols.find(matrix[i - 1][j - 1]) != std::string::npos) {
          sum += 100 * (matrix[i][j] - '0') + 10 * (matrix[i][j + 1] - '0') +
                 (matrix[i][j + 2] - '0');
        }
      }
    }
  }
  // Final sum
  std::cout << "\nSum : " << sum << std::endl;

  return 0;
}

