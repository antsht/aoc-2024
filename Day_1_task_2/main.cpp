#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::unordered_map<unsigned int, unsigned int> data;

  {
    std::ifstream inputFS("input");
    if (inputFS.is_open()) {
      int left, right;
      while (inputFS >> left >> right) {
        data[left] = 0;
      }
    } else {
      std::cerr << "Error: Unable to open input file." << std::endl;
      return 1;
    }
  }

  {
    std::ifstream inputFS("input");
    if (inputFS.is_open()) {
      int left, right;
      while (inputFS >> left >> right) {
        // check if data[right] exists than increment value
        if (data.contains(right)) {
                  data[right]++;
                }
        

      }
    } else {
      std::cerr << "Error: Unable to open input file." << std::endl;
      return 1;
    }
  }

  u_int64_t result = 0;
  for (const auto& [k, v] : data) {
    result += k * v;
  }

  std::cout << result << std::endl;

  return 0;
}