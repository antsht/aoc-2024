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
  
void fillRouteCost(std::vector<std::vector<int>> &grid, std::pair<int, int> start,
                std::pair<int, int> end, std::vector<std::pair<int, int>> &route);

void printMap(std::vector<std::vector<int>> &dataMap);
std::vector<std::vector<int>> loadMap(const std::string &filename,
                                      int &startRow, int &startCol, int &endRow,
                                      int &endCol);

int manhattanDistance(std::pair<int, int> start, std::pair<int, int> end);

#endif // MAIN_HPP