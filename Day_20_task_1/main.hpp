#ifndef MAIN_HPP
#define MAIN_HPP
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// UP, RIGHT, DOWN, LEFT
const std::array<std::pair<int, int>, 4> directions = {
    {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

const int TURN_COST = 0;
const int STEP_COST = 1;
const int INF = std::numeric_limits<int>::max();

struct State {
  int x, y;
  int direction;  // (0: UP, 1: RIGHT, 2: DOWN, 3: LEFT)
  int cost;

  bool operator>(const State &other) const { return cost > other.cost; }
};

int findMinCost(const std::vector<std::vector<int>> &grid, std::pair<int, int> start,
                std::pair<int, int> end);

void printMap(std::vector<std::vector<int>> &dataMap);
std::vector<std::vector<int>> loadMap(const std::string &filename,
                                      int &startRow, int &startCol, int &endRow,
                                      int &endCol);

#endif // MAIN_HPP