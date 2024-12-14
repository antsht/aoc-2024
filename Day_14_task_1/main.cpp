#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::int32_t;
constexpr int32_t ROWS = 103;
constexpr int32_t COLS = 101;
struct robot {
  valueType row;
  valueType col;
  valueType row_velocity;
  valueType col_velocity;
};
void printData(const std::vector<robot> &data);
void makeNStepss(std::vector<robot> &robots, int n);
std::uint64_t calcSafetyFactor(const std::vector<robot> &robots);

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
  makeNStepss(robots, 100);
  printData(robots);

  std::cout << calcSafetyFactor(robots) << std::endl;
  return 0;
}

void makeNStepss(std::vector<robot> &robots, int n) {
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
    std::cout << robot_.row << " " << robot_.col << std::endl;
    map[robot_.row][robot_.col] += 1;
  }

  for (auto &row : map) {
    for (auto &col : row) {
      std::cout << col;
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

std::uint64_t calcSafetyFactor(const std::vector<robot> &robots) {
  std::uint64_t safetyFactor = 0;
  std::vector<std::vector<int>> map(ROWS, std::vector<int>(COLS, 0));
  for (auto &robot_ : robots) {
    std::cout << robot_.row << " " << robot_.col << std::endl;
    map[robot_.row][robot_.col] += 1;
  }
  int64_t q1 = 0;
  int64_t q2 = 0;
  ino64_t q3 = 0;
  int64_t q4 = 0;
  for (size_t i = 0; i < map.size() / 2; ++i) {
    for (size_t j = 0; j < map[0].size() / 2; ++j) {
      q1+=map[i][j];
    }
  }
  for (size_t i = (map.size() / 2) + 1; i < map.size(); ++i) {
    for (size_t j = 0; j < map[0].size() / 2; ++j) {
      q2+=map[i][j];
    }
  }
  for (size_t i = 0; i < map.size() / 2; ++i) {
    for (size_t j = (map[0].size() / 2) + 1; j < map[0].size(); ++j) {
      q3+=map[i][j];
    }
  }
  for (size_t i = (map.size() / 2) + 1; i < map.size(); ++i) {
    for (size_t j = (map[0].size() / 2) + 1; j < map[0].size(); ++j) {
      q4+=map[i][j];
    }
  }
  safetyFactor = q1 * q2 * q3 * q4;

  return safetyFactor;
}