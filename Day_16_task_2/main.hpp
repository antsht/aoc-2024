#ifndef MAIN_HPP
#define MAIN_HPP
#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Direction {
  int i, j;
  bool operator<(const Direction &other) const {
    if (i != other.i) {
      return i < other.i;
    } else {
      return j < other.j;
    }
  }
};

const std::array<Direction, 4> directions{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

int getDirIdx(int i, int j) {
  if (i == 0 && j == 1) return 0;
  if (i == 1 && j == 0) return 1;
  if (i == 0 && j == -1) return 2;
  return 3;
}

int getSign(int x) { return (x > 0) - (x < 0); }

class Labyrinth {
 public:
  Labyrinth(const std::vector<std::vector<int>> dataMap, const Direction &start,
            const Direction &end)
      : dataMap(dataMap),
        rows(dataMap.size()),
        cols(dataMap[0].size()),
        start(start),
        end(end) {
    updateNeighbours(start.i, start.j);
    updateNeighbours(end.i, end.j);

    for (int i = 0; i < static_cast<int>(dataMap.size()); ++i) {
      for (int j = 0; j < static_cast<int>(dataMap[i].size()); ++j) {
        if (dataMap[i][j] == '#' || (i == start.i && j == start.j) ||
            (i == end.i && j == end.j)) {
          continue;
        }

        if (dataMap[i][j] == '.' && isNode(i, j)) {
          updateNeighbours(i, j);
        }
      }
    }
  }

  long dijkstraAlgorithm() {
    std::priority_queue<
        std::pair<long, std::tuple<Direction, Direction, Direction>>,
        std::vector<
            std::pair<long, std::tuple<Direction, Direction, Direction>>>,
        std::greater<>>
        pq;

    pq.push({0, {start, directions[0], start}});
    std::unordered_map<int, std::vector<std::pair<Direction, Direction>>>
        visited;
    while (!pq.empty()) {
      auto [distance, posPrevDirPrev] = pq.top();
      auto [pos, prevDir, prev] = posPrevDirPrev;
      int dirIdx{getDirIdx(getSign(pos.i - prev.i), getSign(pos.j - prev.j))};
      pq.pop();

      if (visited.contains(pos.i * cols * directions.size() +
                           pos.j * directions.size() + dirIdx))
        continue;

      visited[pos.i * cols * directions.size() + pos.j * directions.size() +
              dirIdx]
          .push_back({prev, prevDir});

      auto [cDist, cPosDirPrev] = pq.top();
      auto [cPos, cPrevDir, cPrev] = cPosDirPrev;
      int cDirIdx{
          getDirIdx(getSign(cPos.i - cPrev.i), getSign(cPos.j - cPrev.j))};
      while (cPos.i == pos.i && cPos.j == pos.j && cDist == distance &&
             cDirIdx == dirIdx && !pq.empty()) {
        visited[pos.i * cols * directions.size() + pos.j * directions.size() +
                cDirIdx]
            .push_back({cPrev, cPrevDir});
        pq.pop();
        std::tie(cDist, cPosDirPrev) = pq.top();
        std::tie(cPos, cPrevDir, cPrev) = cPosDirPrev;
        cDirIdx =
            getDirIdx(getSign(cPos.i - cPrev.i), getSign(cPos.j - cPrev.j));
      }

      if (pos.i == end.i && pos.j == end.j) {
        std::unordered_set<int> spots;
        getBestPositions(visited, end, dirIdx, spots);
        return spots.size();
      }

      std::vector<Direction> neighbours{nodes[pos.i * cols + pos.j]};

      for (const auto &n : neighbours) {
        int nDirIdx{getDirIdx(getSign(n.i - pos.i), getSign(n.j - pos.j))};
        bool willTurn{nDirIdx != dirIdx};

        if (visited.contains(n.i * cols * directions.size() +
                             n.j * directions.size() + nDirIdx))
          continue;

        long nDistance{std::abs(n.i - pos.i + n.j - pos.j) + 1000 * willTurn +
                       distance};
        pq.push({nDistance, {n, directions[dirIdx], pos}});
      }
    }

    return -1;
  }

 private:
  const std::vector<std::vector<int>> dataMap;
  const int rows, cols;
  std::unordered_map<int, std::vector<Direction>> nodes;

  const Direction start;
  const Direction end;

  bool isNode(int i, int j) {
    if ((i == start.i && j == start.j) || (i == end.i && j == end.j))
      return true;

    int horizontal{0};
    int vertical{0};
    for (const auto &dir : directions) {
      int ni{i + dir.i};
      int nj{j + dir.j};
      if (!isInBounds(ni, nj)) continue;

      if (dataMap[ni][nj] == '.') {
        if (dir.i)
          ++vertical;
        else
          ++horizontal;
      }
    }
    return vertical > 0 && horizontal > 0;
  }

  bool isInBounds(int i, int j) {
    return i >= 0 && i < static_cast<int>(dataMap.size()) && j >= 0 &&
           j < static_cast<int>(dataMap[i].size());
  }

  void updateNeighbours(const int i, const int j) {
    for (const auto &dir : directions) {
      int ni{i + dir.i};
      int nj{j + dir.j};
      while (isInBounds(ni, nj) && dataMap[ni][nj] != '#') {
        if (isNode(ni, nj)) {
          nodes[i * cols + j].push_back({ni, nj});
          break;
        }

        ni += dir.i;
        nj += dir.j;
      }
    }
  }

  void getBestPositions(
      const std::unordered_map<
          int, std::vector<std::pair<Direction, Direction>>> &paths,
      const Direction &endNode, int dirIdx, std::unordered_set<int> &visited) {
    if (endNode.i == start.i && endNode.j == start.j) {
      visited.insert(start.i * cols + start.j);
      return;
    }

    for (const auto &[prev, prevDir] :
         paths.at(endNode.i * cols * directions.size() +
                  endNode.j * directions.size() + dirIdx)) {
      Direction dir{getSign(prev.i - endNode.i), getSign(prev.j - endNode.j)};
      int i{endNode.i};
      int j{endNode.j};
      while (prev.i != i || prev.j != j) {
        visited.insert(i * cols + j);
        i += dir.i;
        j += dir.j;
      }

      int prevDirIdx{getDirIdx(prevDir.i, prevDir.j)};
      getBestPositions(paths, prev, prevDirIdx, visited);
    }
  }
};

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
        lineData.push_back('.');
        startCol = lineData.size() - 1;
        startRow = dataMap.size();
      } else if (c == 'E') {
        lineData.push_back('.');
        endCol = lineData.size() - 1;
        endRow = dataMap.size();
      } else {
        lineData.push_back(c);
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
        std::cout << '#';
      } else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif  // MAIN_HPP