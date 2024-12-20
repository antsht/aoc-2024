
#include "main.hpp"
#include <iomanip>

int main() {
  std::pair<int, int> start, end;
  std::vector<std::pair<int, int>> route;
  // Load map and moves
  auto dataMap =
      loadMap("./input_s", start.first, start.second, end.first, end.second);

  printMap(dataMap);

  fillRouteCost(dataMap, start, end, route);

  printMap(dataMap);



  return 0;
}

// Load map from file
std::vector<std::vector<int>> loadMap(const std::string &filename,

                                      int &startRow, int &startCol, int &endRow,
                                      int &endCol) {
  std::ifstream inputFS(filename);
  if (!inputFS.is_open()) {
    throw std::runtime_error("Error: Unable to open input file.");
  }

  std::vector<std::vector<int>> dataMap;
  std::string line;
  while (std::getline(inputFS, line)) {
    std::stringstream lineStream(line);
    std::vector<int> lineData;
    char c;
    while (lineStream >> c) {
      if (c == 'S') {
        lineData.push_back(1);
        startCol = lineData.size() - 1;
        startRow = dataMap.size();
      } else if (c == 'E') {
        lineData.push_back(0);
        endCol = lineData.size() - 1;
        endRow = dataMap.size();
      } else if (c == '#') {
        lineData.push_back(-1);
      } else {
        lineData.push_back(0);
      }
    }
    dataMap.push_back(lineData);
  }
  return dataMap;
}

void printMap(std::vector<std::vector<int>> &dataMap) {
  for (const auto &row : dataMap) {
    for (const auto &cell : row) {
      if (cell == -1) {
        std::cout << "###";
      } else {
        // format the number to be 3 digits wide
        std::cout << std::setw(3) << std::setfill('0') << cell;
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void fillRouteCost(std::vector<std::vector<int>> &grid, std::pair<int, int> start,
                std::pair<int, int> end, std::vector<std::pair<int, int>> &route) {

  int rows = grid.size();
  int cols = grid[0].size();
  int x = start.first;
  int y = start.second;
  while(x!=end.first || y!=end.second) {
   route.push_back({x,y});
  for (int new_dir = 0; new_dir < 4; ++new_dir) {
    int nx = x + directions[new_dir].first;
    int ny = y + directions[new_dir].second;

    // Skip if out of bounds or obstacle
    if (nx <= 0 || ny <= 0 || nx >= rows - 1 || ny >= cols - 1) {
      continue;
    }
    if (grid[nx][ny] == 0) {
      grid[nx][ny] = grid[x][y] + 1;
      x = nx;
      y = ny;
      break;
    }
  }

  }
  route.push_back({x,y});
  return;
}
