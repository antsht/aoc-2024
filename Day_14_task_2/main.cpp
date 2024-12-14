#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::int32_t;
constexpr int32_t ROWS = 103; // 103;
constexpr int32_t COLS = 101;  // 101;
struct robot {
  valueType row;
  valueType col;
  valueType row_velocity;
  valueType col_velocity;
};
void printData(const std::vector<robot> &data);
void makeNSteps(std::vector<robot> &robots, int n);
bool isXMASTree(const std::vector<robot> &robots);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<robot> robots;
  std::string line;
  while (std::getline(inputFS, line)) {
    if (line.empty()) {
      continue;
    }
    robot newRobot{};
    sscanf(line.c_str(), "p=%d,%d v=%d,%d", &(newRobot.col), &(newRobot.row),
           &(newRobot.col_velocity), &(newRobot.row_velocity));
    robots.push_back(newRobot);
  }
  inputFS.close();

  printData(robots);
  size_t seconds_passed = 0;
  while (1) {
    makeNSteps(robots, 1);
    seconds_passed++;
    if (isXMASTree(robots)) {
      printData(robots);
      std::cout << "Seconds passed: " << seconds_passed << std::endl;
      std::cin.get();
    }
  }
  return 0;
}

void makeNSteps(std::vector<robot> &robots, int n) {
  for (auto &robot_ : robots) {
    robot_.row = (robot_.row + n * robot_.row_velocity) % ROWS;
    if (robot_.row < 0) {
      robot_.row += ROWS;
    }
    robot_.col = (robot_.col + n * robot_.col_velocity) % COLS;
    if (robot_.col < 0) {
      robot_.col += COLS;
    }
  }
}

void printData(const std::vector<robot> &data) {
  std::vector<std::vector<int>> map(ROWS, std::vector<int>(COLS, 0));
  for (auto &robot_ : data) {
    //std::cout << robot_.row << " " << robot_.col << std::endl;
    map[robot_.row][robot_.col] += 1;
  }

  for (auto &row : map) {
    for (auto &col : row) {
      std::cout << col;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << std::endl;
}

bool isXMASTree(const std::vector<robot> &robots) {
  std::vector<std::vector<int>> map(ROWS, std::vector<int>(COLS, 0));
  for (auto &robot_ : robots) {
    map[robot_.row][robot_.col] = 1;
  }
  bool result = false;
  for (size_t i = 1; i < ROWS-1; ++i) {
    for (size_t j = 1; j < COLS-1; ++j) {
      if (map[i][j] == 1) {
        if (map[i - 1][j-1] == 1 && map [i - 1][j] == 1 && map[i - 1][j+1] == 1 && map[i][j-1] == 1 && map[i][j+1] == 1 && map[i+1][j-1] == 1 && map[i+1][j] == 1 && map[i+1][j+1] == 1) {
          result = true;
        }
      }
    }
  }
  return result;
}