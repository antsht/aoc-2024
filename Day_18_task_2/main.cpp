
#include "main.hpp"

int main() {
    std::pair<int, int> start, end;

    // Load map and moves
    // JUST USED BINARY SEARCH TO FIND FIRST BLOCKING COORDINATE
    auto dataMap = loadMap("./input_test_s", start.first, start.second, end.first, end.second, 2954);

    printMap(dataMap);



    int result = findMinCost(dataMap, start, end);

    if (result != -1) {
        std::cout << "Cheapest route: " << result << std::endl;
  } else {
    std::cout << "There is no route" << std::endl;
  }

  return 0;
}

// Load map from file
std::vector<std::vector<int>> loadMap(const std::string &filename,
                                       
                                       int &startRow, int &startCol, int &endRow, int &endCol, int byteToRead) {
  std::ifstream inputFS(filename);
  if (!inputFS.is_open()) {
    throw std::runtime_error("Error: Unable to open input file.");
  }
startRow=1;;
startCol=1;
endRow=71;
endCol=71;
  // Read the map from the file
//create vector 7 rows x 7 cols
size_t dimension = 71;
  std::vector<std::vector<int>> dataMap(dimension+2, std::vector<int>(dimension+2, 1));
  for (size_t i = 0; i < dimension+2; ++i) {
    dataMap[i][0] = 0;
    dataMap[i][dimension+1] = 0;
    dataMap[0][i] = 0;
    dataMap[dimension+1][i] = 0;
  }
  


  std::string line;
  while (std::getline(inputFS, line)) {
    if (byteToRead==0){
      break;
    }
    int32_t row, col;
    sscanf(line.c_str(), "%d, %d", &col, &row);
    dataMap[row+1][col+1]=0;
    byteToRead--;
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