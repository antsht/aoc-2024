#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void rotateRight(int &rowDir, int &colDir);
void move(int &row, int &col, int &dirRow, int &dirCol,
          std::vector<std::vector<char>> &dataMap);

int main() {

  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::string line;
  int startRow = 0;
  int startCol = 0;
  int dirRow = -1;
  int dirCol = 0;
  std::vector<std::vector<char>> dataMap;
  while (std::getline(inputFS, line)) {
    std::stringstream lineStream(line);
    std::vector<char> lineData;
    char c;
    while (lineStream >> c) {
      lineData.push_back(c);
      if (c == '^') {
        startCol = lineData.size() - 1;
        startRow = dataMap.size();
      }
    }
    dataMap.push_back(lineData);
  }
  inputFS.close();

  for (size_t i = 0; i < 5000; ++i) {
    move(startRow, startCol, dirRow, dirCol, dataMap);
  }
  // print dataMap
  for (const auto &row : dataMap) {
    for (const auto &c : row) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  // print start coords
  std::cout << "startRow: " << startRow << std::endl;
  std::cout << "startCol: " << startCol << std::endl;
  std::cout << dataMap[startRow][startCol] << std::endl;

  // count all 'X' in dataMap
  int count = 0;
  for (const auto &row : dataMap) {
    for (const auto &c : row) {
      if (c == 'X') {
        ++count;
      }
    }
  }

  std::cout << count << std::endl;
  return 0;
}

void rotateRight(int &rowDir, int &colDir) {
  if (rowDir == -1 && colDir == 0) {
    rowDir = 0;
    colDir = 1;
  } else if (rowDir == 0 && colDir == 1) {
    rowDir = 1;
    colDir = 0;
  } else if (rowDir == 1 && colDir == 0) {
    rowDir = 0;
    colDir = -1;
  } else if (rowDir == 0 && colDir == -1) {
    rowDir = -1;
    colDir = 0;
  }
}

void move(int &row, int &col, int &dirRow, int &dirCol,
          std::vector<std::vector<char>> &dataMap) {
  dataMap[row][col] = 'X';
  if (dataMap[row + dirRow][col + dirCol] == '#' || (row + dirRow) < 0 ||
      (row + dirRow) >= (static_cast<int>(dataMap.size()) - 1) ||
      (col + dirCol) < 0 ||
      (col + dirCol) >= (static_cast<int>(dataMap.size()) - 1)) {
    rotateRight(dirRow, dirCol);
  } else {
    row += dirRow;
    col += dirCol;
  }
}