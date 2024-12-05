#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

std::uint32_t countX_MAS(const std::vector<std::string> &data, size_t i, size_t j);

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

  for (size_t i = 1; i < data.size()-1; ++i) {
    for (size_t j = 1; j < data[i].size()-1; ++j) {
      if (data[i][j] == 'A') {
        result += countX_MAS(data, i, j);
      }
    }
  }


  std::cout << result << std::endl;

  return 0;
}

std::uint32_t countX_MAS(const std::vector<std::string> &data, size_t i,
                         size_t j) {
  const std::vector<std::array<char, 4>> patterns = {{'M', 'S', 'M', 'S'},
                                                     {'S', 'M', 'M', 'S'},
                                                     {'M', 'S', 'S', 'M'},
                                                     {'S', 'M', 'S', 'M'}};

  std::array<char, 4> actualChars = {
      data[i - 1][j - 1],  // Top-left
      data[i + 1][j + 1],  // Bottom-right
      data[i - 1][j + 1],  // Top-right
      data[i + 1][j - 1]   // Bottom-left
  };

  return std::count(patterns.begin(), patterns.end(), actualChars);
}