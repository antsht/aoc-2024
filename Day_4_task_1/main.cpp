#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::uint32_t countXMAS(const std::vector<std::string> &data, size_t i,
                        size_t j);

int main() {
  std::ifstream inputFS("./input");

  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  // read from inputFS to vactor<std::string>
  std::vector<std::string> data;
  std::string line;
  while (std::getline(inputFS, line)) {
    data.push_back(line);
  }
  inputFS.close();

  std::uint32_t result = 0;

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data[i].size(); ++j) {
      if (data[i][j] == 'X') {
        result += countXMAS(data, i, j);
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}

std::uint32_t countXMAS(const std::vector<std::string> &data, size_t i,
                        size_t j) {
  std::uint32_t result = 0;

  std::vector<std::pair<int, int>> directions = {
      {0, -1},   // Left
      {0, 1},    // Right
      {-1, 0},   // Up
      {1, 0},    // Down
      {-1, -1},  // Up-Left
      {-1, 1},   // Up-Right
      {1, -1},   // Down-Left
      {1, 1}     // Down-Right
  };

  const char expected[] = {'M', 'A', 'S'};

  for (const auto &dir : directions) {
    int di = dir.first;
    int dj = dir.second;
    bool valid = true;
    for (int k = 1; k <= 3; ++k) {
      size_t ni = i + di * k;
      size_t nj = j + dj * k;
      if (ni >= data.size() || nj >= data[ni].size()) {
        valid = false;
        break;
      }
      if (data[ni][nj] != expected[k - 1]) {
        valid = false;
        break;
      }
    }
    if (valid) {
      ++result;
    }
  }
  return result;
}