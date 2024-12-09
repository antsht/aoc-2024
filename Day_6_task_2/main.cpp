#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void rotateRight(int &rowDir, int &colDir);
bool move(int &row, int &col, int &dirRow, int &dirCol,
          const std::vector<std::vector<char>> &dataMap);

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
        // print
        std::cout << "Start: " << startRow << " " << startCol << std::endl;
      }
    }
    dataMap.push_back(lineData);
  }
  inputFS.close();

  int sentinelsCount = 0;
  int maxSteps = dataMap.size() * dataMap[0].size()*40;

  for (size_t r = 0; r < dataMap.size(); ++r) {
    for (size_t c = 0; c < dataMap[0].size(); ++c) {
      if (dataMap[r][c] == '.') {
        dataMap[r][c] = '#';
        int row = startRow;
        int col = startCol;
        dirRow = -1;
        dirCol = 0;
        int steps = maxSteps;
        while ((row + dirRow) >= 0 &&
               (row + dirRow) < static_cast<int>(dataMap.size()) &&
               (col + dirCol) >= 0 &&
               (col + dirCol) < static_cast<int>(dataMap[0].size())) {
          move(row, col, dirRow, dirCol, dataMap);
          if (--steps == 0) {
            ++sentinelsCount;
            std::cout << "Found: " << r << " : " << c << "Total: "
                      << sentinelsCount << std::endl;
            break;
          }
        }

        dataMap[r][c] = '.';
      }
    }
  }
  // print start coords
  std::cout << "startRow: " << startRow << std::endl;
  std::cout << "startCol: " << startCol << std::endl;
  // print dataMap
  std::cout << dataMap[startRow][startCol] << std::endl;

  for (const auto &row : dataMap) {
    for (const auto &c : row) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  // print result
  std::cout << sentinelsCount << std::endl;

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

bool move(int &row, int &col, int &dirRow, int &dirCol,
          const std::vector<std::vector<char>> &dataMap) {
  if (dataMap[row + dirRow][col + dirCol] == '#') {
    rotateRight(dirRow, dirCol);

    return true;
  } else {
    row += dirRow;
    col += dirCol;
  }
  return false;
}
