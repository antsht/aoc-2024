
#include "main.hpp"

int main() {
    std::pair<int, int> start, end;

    // Load map and moves
    auto dataMap = loadMap("./input", start.first, start.second, end.first, end.second);

    printMap(dataMap);



    int result = findMinCost(dataMap, start, end);

    if (result != -1) {
        std::cout << "Cheapest route: " << result << std::endl;
  } else {
    std::cout << "There is no route" << std::endl;
  }
  size_t goodImprovements = 0;
  for (size_t i = 1; i < dataMap.size()-1; ++i) {
    for (size_t j = 1; j < dataMap[i].size() - 1; ++j) {
      if (dataMap[i][j] == 0) {
        auto mapCopy = dataMap;
        mapCopy[i][j] = 1;
        int newResult = findMinCost(mapCopy, start, end);
        if (newResult != -1 && newResult < result) {
          std::cout << "i: " << i << " j: " << j << " Improvement: " << result-newResult
                    << std::endl;
                    if (result - newResult >=100) {
                      goodImprovements++;
                    }
        }     
      }
    }
    std::cout << std::endl;
  }
std::cout << "Good improvements: " << goodImprovements << std::endl;
  return 0;
}

// Load map from file
std::vector<std::vector<int>> loadMap(const std::string &filename,
                                       
                                       int &startRow, int &startCol, int &endRow, int &endCol) {
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

void printMap(std::vector<std::vector<int>> &dataMap) {
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



int findMinCost(const std::vector<std::vector<int>> &grid,
                std::pair<int, int> start, std::pair<int, int> end) {
  int rows = grid.size();
  int cols = grid[0].size();

  // Set minimum cost for each cell and direction to infinity
  std::vector<std::vector<std::vector<int>>> minCost(
      rows, std::vector<std::vector<int>>(cols, std::vector<int>(4, INF)));

  std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

  // Push starting point with direction to the right as required
  pq.push({start.first, start.second, 1, 0});
  minCost[start.first][start.second][1] = 0;

  while (!pq.empty()) {
    State current = pq.top();
    pq.pop();

    int x = current.x;
    int y = current.y;
    int dir = current.direction;
    int cost = current.cost;

    // finish is found, return the cost
    if (x == end.first && y == end.second) {
      return cost;
    }

    // Skip if the cost is higher than the minimum cost for this cell and
    // direction
    if (cost > minCost[x][y][dir]) {
      continue;
    }

    // Iterate over neighbors
    for (int new_dir = 0; new_dir < 4; ++new_dir) {
      int nx = x + directions[new_dir].first;
      int ny = y + directions[new_dir].second;

      // Skip if out of bounds or obstacle
      if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] == 0) {
        continue;
      }

      // Calculate cost for moving to the new cell
      int turnCost = (dir == new_dir) ? 0 : TURN_COST;
      int newCost = cost + STEP_COST + turnCost;

      // Update the minimum cost if it's lower
      if (newCost < minCost[nx][ny][new_dir]) {
        minCost[nx][ny][new_dir] = newCost;
        pq.push({nx, ny, new_dir, newCost});
      }
    }
  }

  // If path is not found
  return -1;
}