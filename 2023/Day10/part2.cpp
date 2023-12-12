#include <cmath>
#include <iostream>
#include <vector>

// function tp return signed angle
double get_angle(std::vector<int> *point, std::vector<int> *p1,
                 std::vector<int> *p2) {
  std::vector<int> v1;
  std::vector<int> v2;
  v1.push_back(p1->at(0) - point->at(0));
  v1.push_back(p1->at(1) - point->at(1));
  v2.push_back(p2->at(0) - point->at(0));
  v2.push_back(p2->at(1) - point->at(1));

  double dot = (v1[0] * v2[0]) + (v1[1] * v2[1]);
  double det = v1[0] * v2[1] - v1[1] * v2[0];
  double angle2 = (-1) * atan2(det, dot);
  return angle2 * 180.0 / M_PI;
}

int main() {
  std::vector<std::vector<char>> matrix;
  std::string line;

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

  std::clog << "Input taken." << std::endl;

  int steps{0};
  char symbol;

  // Start to the right of 'S' (from looking at input)
  unsigned int r{rs};
  unsigned int c{cs + 1};
  std::string dirn{"right"};

  std::vector<std::vector<unsigned int>> coordinates;
  // Traverse the path and get coordinates of vertices
  while (1) {
    if (r == rs && c == cs) {
      std::vector<unsigned int> temp;
      temp.push_back(r);
      temp.push_back(c);
      coordinates.push_back(temp);
      break;
    }

    symbol = matrix[r][c];

    if (symbol == '-') {
      // Replace path symbols
      matrix[r][c] = 'S';
      if (dirn == "right") {
        c++;
      } else if (dirn == "left") {
        c--;
      }
    } else if (symbol == 'J') {
      matrix[r][c] = 'S';
      std::vector<unsigned int> temp;
      temp.push_back(r);
      temp.push_back(c);
      coordinates.push_back(temp);
      if (dirn == "right") {
        r--;
        dirn = "up";
      } else if (dirn == "down") {
        c--;
        dirn = "left";
      }
    } else if (symbol == '|') {
      matrix[r][c] = 'S';
      if (dirn == "up") {
        r--;
      } else if (dirn == "down") {
        r++;
      }
    } else if (symbol == '7') {
      matrix[r][c] = 'S';
      std::vector<unsigned int> temp;
      temp.push_back(r);
      temp.push_back(c);
      coordinates.push_back(temp);
      if (dirn == "up") {
        c--;
        dirn = "left";
      } else if (dirn == "right") {
        r++;
        dirn = "down";
      }
    } else if (symbol == 'F') {
      matrix[r][c] = 'S';
      std::vector<unsigned int> temp;
      temp.push_back(r);
      temp.push_back(c);
      coordinates.push_back(temp);
      if (dirn == "left") {
        r++;
        dirn = "down";
      } else if (dirn == "up") {
        c++;
        dirn = "right";
      }
    } else if (symbol == 'L') {
      matrix[r][c] = 'S';
      std::vector<unsigned int> temp;
      temp.push_back(r);
      temp.push_back(c);
      coordinates.push_back(temp);
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

  std::clog << "Steps counted." << std::endl;

  std::clog << "Steps : " << (steps + 1) / 2 << std::endl;

  unsigned int enclosed{0};
  // Check sum of angles projected from all sides of the path
  for (auto i = 0U; i < matrix.size(); i++) {
    for (auto j = 0U; j < matrix[0].size(); j++) {
      // Chec whether point is on path
      if (matrix[i][j] == 'S') {
        continue;
      } else {
        std::vector<int> point;
        point.push_back(static_cast<int>(j));
        point.push_back(static_cast<int>(i) * (-1));
        double angle_sum{0};
        for (auto k = 0U; k < coordinates.size(); k++) {
          std::vector<int> p1;
          p1.push_back(static_cast<int>(coordinates[k][1]));
          p1.push_back(static_cast<int>(coordinates[k][0]) * (-1));

          std::vector<int> p2;
          if (k == coordinates.size() - 1) {
            p2.push_back(static_cast<int>(coordinates[0][1]));
            p2.push_back(static_cast<int>(coordinates[0][0]) * (-1));
          } else {
            p2.push_back(static_cast<int>(coordinates[k + 1][1]));
            p2.push_back(static_cast<int>(coordinates[k + 1][0]) * (-1));
          }

          double angle = get_angle(&point, &p1, &p2);
          angle_sum += angle;
        }
        // Equate sum of angles to 360
        if (std::abs(std::abs(angle_sum) - 360) < 10) {
          enclosed++;
        }
      }
    }
  }

  std::clog << "Enclosed points : " << enclosed << std::endl;

  return 0;
}

