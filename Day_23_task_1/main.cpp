#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

// Function to find all triangles in the graph
int findTriangles(const std::unordered_map<int, std::unordered_set<int>>& graph) {
  int count = 0;
    for (const auto& [node1, neighbors1] : graph) {
        for (const auto& node2 : neighbors1) {
            if (node2 > node1) {  // Avoid duplicate checks
                for (const auto& node3 : graph.at(node2)) {
                    if (node3 > node2 && graph.at(node3).count(node1)) {
                        std::cout << "{" << node1 << ", " << node2 << ", " << node3 << "}" << std::endl;
                        if ((node1>> 8) == 't' || (node2 >> 8) == 't' || (node3 >> 8) == 't') {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {

 std::unordered_map<int, std::unordered_set<int>> links;

  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  std::string line;

  std::set<std::tuple<int, int, int>> threes;
  while (std::getline(inputFS, line)) {
    if (line.empty()) {
      continue;
    }
    char a, b, c, d;
    sscanf(line.c_str(), "%c%c-%c%c", &a, &b, &c, &d);
    std::cout << a << " " << b << " " << c << " " << d << std::endl;
    uint16_t p1 = (a << 8) + b;
    uint16_t p2 = (c << 8) + d;
    std::cout << p1 << " " << p2 << std::endl;
      links[p2].insert(p1);
      links[p1].insert(p2);
  }
  inputFS.close();
 
 
 std::cout << findTriangles(links) << std::endl;

  return 0;
}


