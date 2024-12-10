#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;
void printData(const std::vector<std::string> &data);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<std::string> data;
  std::string line;
  while (std::getline(inputFS, line)) {
    data.push_back(line);
  }
  inputFS.close();
  printData(data);

  auto dataNew = data;
  size_t max_row = data.size();
  size_t max_col = data[0].size();
  for (size_t row = 0; row < max_row; ++row) {
    for (size_t col = 0; col < max_col; ++col) {
      if (data[row][col] != '.') {
        char current = data[row][col];
        for (size_t inner_row = row; inner_row < max_row; ++inner_row) {
          for (size_t inner_col = 0; inner_col < max_col; ++inner_col) {
            if (inner_row == row && inner_col <= col) {
              continue;
            }
            if (data[inner_row][inner_col] == current) {
              int new_r1, new_c1, new_r2, new_c2;
              new_r1 = row - (inner_row - row);
              new_c1 = col - (inner_col - col);
              new_r2 = inner_row + (inner_row - row);
              new_c2 = inner_col + (inner_col - col);
              if (new_r1 >= 0 && new_r1 < static_cast<int>(max_row) &&
                  new_c1 >= 0 && new_c1 < static_cast<int>(max_col)) {
                dataNew[new_r1][new_c1] = '#';
              }
              if (new_r2 >= 0 && new_r2 < static_cast<int>(max_row) &&
                  new_c2 >= 0 && new_c2 < static_cast<int> (max_col)) {
                dataNew[new_r2][new_c2] = '#';
              }
            }
          }
        }
      }
    }
  }

  printData(dataNew);

  // count the number of #
  size_t count = 0;
  for (auto &row : dataNew) {
    for (auto &col : row) {
      if (col == '#') {
        ++count;
      }
    }
  }
  std::cout << "Number of #: " << count << std::endl;
  return 0;
}

void printData(const std::vector<std::string> &data) {
  for (auto &row : data) {
    std::cout << row;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
