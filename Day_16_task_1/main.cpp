#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void printMap(std::vector<std::vector<uint32_t>> &dataMap);
std::vector<std::vector<uint32_t>> loadMap(const std::string &filename,
                                       uint32_t &startRow, uint32_t &startCol, uint32_t &endRow, uint32_t &endCol);

int main() {
  uint32_t startRow = 0;
  uint32_t startCol = 0;
  uint32_t endRow = 0;
  uint32_t endCol = 0;

  // Load map and moves
  auto dataMap = loadMap("./input_test_s", startRow, startCol, endRow, endCol);

  printMap(dataMap);
 
  return 0;
}

// Load map from file
std::vector<std::vector<uint32_t>> loadMap(const std::string &filename,
                                       
                                       uint32_t &startRow, uint32_t &startCol, uint32_t &endRow, uint32_t &endCol) {
  std::ifstream inputFS(filename);
  if (!inputFS.is_open()) {
    throw std::runtime_error("Error: Unable to open input file.");
  }

  std::vector<std::vector<uint32_t>> dataMap;
  std::string line;
  while (std::getline(inputFS, line)) {
    std::stringstream lineStream(line);
    std::vector<uint32_t> lineData;
    char c;
    while (lineStream >> c) {
      if (c == 'S') {
        lineData.push_back(1);
        startCol = lineData.size() - 1;
        startRow = dataMap.size();
      } else if (c == 'E') {
        lineData.push_back(1);
        endCol = lineData.size() - 1;
        endRow = dataMap.size();
      } else if (c == '#') {
        lineData.push_back(0);
      } else {
        lineData.push_back(1);
      }
    }
    dataMap.push_back(lineData);
  }
  return dataMap;
}

void printMap(std::vector<std::vector<uint32_t>> &dataMap) {
  for (const auto &row : dataMap) {
    for (const auto &cell : row) {
      if (cell == 0) {
        std::cout << '#';}
        else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
