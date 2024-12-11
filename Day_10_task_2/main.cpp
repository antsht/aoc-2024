#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;

void printData(const std::vector<std::vector<int>> &data);

int calculateScore(const std::vector<std::vector<int>> &data, int startRow,
                   int startCol);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<std::vector<int>> data;
  std::string line;
  while (std::getline(inputFS, line)) {
    std::istringstream iss(line);
    std::vector<int> line;
    char c;
    while (iss >> c) {
      line.push_back(c - '0');
    }
    data.push_back(line);
  }
  inputFS.close();
  printData(data);

  int score{0};

  for (int row = 0; row < static_cast<int>(data.size()); ++row) {
    for (int col = 0; col < static_cast<int>(data[row].size()); ++col) {
      if (data[row][col] == 0) {
        score += calculateScore(data, row, col);
      }
    }
  }
  std::cout << "Score: " << score << std::endl;
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

int calculateScore(const std::vector<std::vector<int>> &data, int startRow,
                   int startCol) {
  std::multiset<std::pair<int, int>> startPoints;
  startPoints.insert({startRow, startCol});
  std::multiset<std::pair<int, int>> endPoints;
  for (int i = 1; i <= 9; ++i) {
    endPoints.clear();
    for (auto &point : startPoints) {
      if ((point.first + 1) < static_cast<int>(data.size()) &&
          data[point.first + 1][point.second] == i) {
        endPoints.insert({point.first + 1, point.second});
      }
      if ((point.first - 1) >= 0 &&
          data[point.first - 1][point.second] == i) {
        endPoints.insert({point.first - 1, point.second});
      }
      if ((point.second + 1) < static_cast<int>(data[0].size()) &&
          data[point.first][point.second + 1] == i) {
        endPoints.insert({point.first, point.second + 1});
      }
      if ((point.second - 1) >= 0 &&
          data[point.first][point.second - 1] == i) {
        endPoints.insert({point.first, point.second - 1});
      }
    }
    startPoints = endPoints;
  }
  std::cout << "Point: " << startRow << ", " << startCol << " Rank: "<< startPoints.size() << std::endl;
  return startPoints.size();
}