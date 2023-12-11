#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  std::string line;

  std::unordered_map<unsigned long int, unsigned long int> galaxies_in_row;
  std::unordered_map<unsigned long int, unsigned long int> galaxies_in_column;

  std::vector<std::vector<unsigned long int>> galaxy_coordinates;

  unsigned long int row{0};

  while (std::getline(std::cin, line)) {
    if (line == " " || line == "") {
      break;
    }

    galaxies_in_row.insert({row, 0});
    unsigned long int column{0};

    for (auto i : line) {
      if (galaxies_in_column.count(column) == 0) {
        galaxies_in_column.insert({column, 0});
      }
      if (i == '#') {
        galaxies_in_row[row] += 1;
        galaxies_in_column[column] += 1;
        std::vector<unsigned long int> temp;
        temp.push_back(row);
        temp.push_back(column);
        galaxy_coordinates.push_back(temp);
      }
      column++;
    }

    row++;
  }

  // get empty rows, sort them, add exapnsion
  std::vector<unsigned long int> empty_rows;
  for (const auto &pair : galaxies_in_row) {
    if (pair.second == 0) {
      empty_rows.push_back(pair.first);
    }
  }
  std::sort(empty_rows.begin(), empty_rows.end());
  for (unsigned long int i = 0; i < empty_rows.size(); i++) {
    empty_rows[i] += i;
  }

  std::vector<unsigned long int> empty_columns;
  for (const auto &pair : galaxies_in_column) {
    if (pair.second == 0) {
      empty_columns.push_back(pair.first);
    }
  }
  std::sort(empty_columns.begin(), empty_columns.end());
  for (unsigned long int i = 0; i < empty_columns.size(); i++) {
    empty_columns[i] += i;
  }

  // Add row expansions
  for (auto i = 0UL; i < empty_rows.size(); i++) {
    for (auto j = 0UL; j < galaxy_coordinates.size(); j++) {
      if (galaxy_coordinates[j][0] > empty_rows[i]) {
        galaxy_coordinates[j][0]++;
      }
    }
  }

  // Add column expansions
  for (auto i = 0UL; i < empty_columns.size(); i++) {
    for (auto j = 0UL; j < galaxy_coordinates.size(); j++) {
      if (galaxy_coordinates[j][1] > empty_columns[i]) {
        galaxy_coordinates[j][1]++;
      }
    }
  }

  // Calculate path lengths
  unsigned long int total_sum{0};
  for (unsigned long int i = 0; i < galaxy_coordinates.size(); i++) {
    for (unsigned long int j = i + 1; j < galaxy_coordinates.size(); j++) {
      unsigned long int sum{0};
      sum += std::max(galaxy_coordinates[j][0], galaxy_coordinates[i][0]) -
             std::min(galaxy_coordinates[j][0], galaxy_coordinates[i][0]);

      sum += std::max(galaxy_coordinates[j][1], galaxy_coordinates[i][1]) -
             std::min(galaxy_coordinates[j][1], galaxy_coordinates[i][1]);
      total_sum += sum;
    }
  }

  std::cout << "Total sum : " << total_sum << std::endl;

  return 0;
}

