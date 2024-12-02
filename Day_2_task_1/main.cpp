#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::uint32_t result = 0;
  {
    std::ifstream inputFS("./input");

    if (!inputFS.is_open()) {
      std::cerr << "Error: Unable to open input file." << std::endl;
      return 1;
    }

    std::string line;
    while (std::getline(inputFS, line)) {
      std::istringstream lineStream(line);
      std::vector<int> numbers;
      int num;

      while (lineStream >> num) {
        numbers.push_back(num);
      }
      bool ascOrder = (numbers[0] < numbers[1]);
      bool isSafe = true;
      for (size_t i = 0; isSafe && (i < (numbers.size()-1)); ++i) {
        
        if (ascOrder && !(((numbers[i + 1] - numbers[i]) >= 1) &&
                          ((numbers[i + 1] - numbers[i]) <= 3))) {
            isSafe = false;
        }
        if (!ascOrder && !(((numbers[i] - numbers[i+1]) >= 1) &&
                          ((numbers[i] - numbers[i+1]) <= 3))) {
            isSafe = false;
        }
      }
      if (isSafe) {
        ++result;
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}