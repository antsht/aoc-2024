
#include "main.hpp"

int main() {
  Direction start, end;

  // Load map and moves
  auto dataMap = loadMap("./input", start.i, start.j, end.i, end.j);

  // printMap(dataMap);

  Labyrinth maze(dataMap, start, end);

  std::cout << "Total good spots: " << maze.dijkstraAlgorithm() << "\n";

  return 0;
}
