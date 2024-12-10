#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using valueType = std::uint64_t;

void printData(const std::vector<std::vector<int>> &data);

int calculateScore(const std::vector<std::vector<int>> &data, size_t startRow,
                   size_t startCol);

int main() {
  std::ifstream inputFS("./input_test");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<std::vector<int>> data;
  std::string line;
  while (std::getline(inputFS, line)) {
    std::istringstream iss(line);
    std::vector<int> line;
    int c;
    while (iss >> c) {
      line.push_back(c);
    }
    data.push_back(line);
  }
  inputFS.close();
  printData(data);

  int score{0};

  for (size_t row = 0; row < data.size(); ++row) {
    for (size_t col = 0; col < data[row].size(); ++col) {
      if (data[row][col] == '0') {
        score += calculateScore(data, row, col);
      }
    }
  }
    return 0;
  }

  void printData(const std::vector<std::vector<int>> &data) {
    for (auto &row : data) {
      for (auto &col : row) {
        std::cout << col;
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  int calculateScore(const std::vector<std::vector<int>> &data, size_t startRow,
                     size_t startCol) {
    std::set<std::pair<size_t, size_t>> startPoints;
    startPoints.insert({startRow, startCol});
    std::set<std::pair<size_t, size_t>> endPoints;
    for (size_t i = 1; i <= 9; ++i) {
      

    }
    return 0;
  }