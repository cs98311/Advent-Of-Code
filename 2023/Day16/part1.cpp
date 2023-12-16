#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  // layout of contraption
  std::vector<std::vector<char>> layout;

  // fill in the layout from input
  std::ifstream in;
  in.open("input.txt");
  if (!in.is_open()) {
    std::clog << "file not open\n";
  } else {
    while (!in.eof()) {
      std::string line;
      std::getline(in, line);
      if (line.empty()) {
        break;
      }
      std::vector<char> temp;
      for (auto i : line) {
        temp.push_back(i);
      }
      layout.push_back(temp);
    }
  }
  in.close();

  // boundaries of the layout
  unsigned long int col_last = layout[0].size() - 1;
  unsigned long int row_last = layout.size() - 1;

  // Energized coordiantes
  // https://stackoverflow.com/questions/51699221/using-unordered-map-to-store-key-value-pairs-in-stl

  std::unordered_map<std::string,
                     std::unordered_map<unsigned long int, unsigned long int>>
      energized_map;

  // light sources: row, column, direction (4/2/6/8)
  std::vector<std::vector<unsigned long int>> sources{{0, 0, 6}};
  for (auto i{0U}; i < sources.size(); i++) {
    unsigned long int row{sources[i][0]};
    unsigned long int col{sources[i][1]};
    unsigned long int dir{sources[i][2]};

    while (1) {
      // store energized tile coods as string in a map
      std::string cood{std::to_string(row) + " " + std::to_string(col)};
      if (energized_map[cood].count(dir) > 0) {
        break;
      } else {
        energized_map[cood][dir]++;
      }

      // Empty space '.'
      if (layout[row][col] == '.') {
        if (dir == 6 && col < col_last) {
          col++;
        } else if (dir == 8 && row > 0) {
          row--;
        } else if (dir == 4 && col > 0) {
          col--;
        } else if (dir == 2 && row < row_last) {
          row++;
        } else {
          break;
        }
      }

      // Splitter '-'
      else if (layout[row][col] == '-') {
        if (dir == 6 && col < col_last) {
          col++;
        } else if (dir == 4 && col > 0) {
          col--;
        } else if (dir == 8 || dir == 2) {
          if (col > 0) {
            sources.push_back({row, col - 1, 4});
          }
          if (col < col_last) {
            sources.push_back({row, col + 1, 6});
          }
          break;
        }
      }

      // Splitter '|'
      else if (layout[row][col] == '|') {
        if (dir == 8 && row > 0) {
          row--;
        } else if (dir == 2 && row < row_last) {
          row++;
        } else if (dir == 4 || dir == 6) {
          if (row < row_last) {
            sources.push_back({row + 1, col, 2});
          }
          if (row > 0) {
            sources.push_back({row - 1, col, 8});
          }
          break;
        } else {
          break;
        }
      }

      // Mirror '/'
      else if (layout[row][col] == '/') {
        if (dir == 2 && col > 0) {
          col--;
          dir = 4;
        } else if (dir == 6 && row > 0) {
          row--;
          dir = 8;
        } else if (dir == 8 && col < col_last) {
          col++;
          dir = 6;
        } else if (dir == 4 && row < row_last) {
          row++;
          dir = 2;
        } else {
          break;
        }
      }

      // Mirror '\'
      else if (layout[row][col] == '\\') {
        if (dir == 2 && col < col_last) {
          col++;
          dir = 6;
        } else if (dir == 6 && row < row_last) {
          row++;
          dir = 2;
        } else if (dir == 8 && col > 0) {
          col--;
          dir = 4;
        } else if (dir == 4 && row > 0) {
          row--;
          dir = 8;
        } else {
          break;
        }
      }
    }
  }

  std::ofstream out;
  out.open("out2.txt");
  assert(out.is_open());
  out << "Total energized tiles : " << energized_map.size() << std::endl;
  out.close();

  return 0;
}

