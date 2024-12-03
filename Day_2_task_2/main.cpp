#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

bool isSafe(const std::vector<int> &numbers);

int main() {
  std::uint32_t result = 0;

  std::ifstream inputFS("./input");

  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(inputFS, line)) {
    std::istringstream lineStream(line);
    std::vector<int> numbers{std::istream_iterator<int>(lineStream),
                             std::istream_iterator<int>()};

    if (isSafe(numbers)) {
      ++result;
      continue;
    }

    for (size_t i = 0; i < numbers.size(); ++i) {
      std::vector<int> newNumbers = numbers;
      newNumbers.erase(newNumbers.begin() + i);
      if (isSafe(newNumbers)) {
        ++result;
        break;
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}

bool isSafe(const std::vector<int> &numbers) {
  if (numbers.size() < 2) {
    return true;
  }
  bool ascOrder = (numbers[0] < numbers[1]);
  bool isSafe = true;
  for (size_t i = 0; i < numbers.size() - 1; ++i) {
    int diff =
        ascOrder ? numbers[i + 1] - numbers[i] : numbers[i] - numbers[i + 1];
    if (diff < 1 || diff > 3) {
      return false;
    }
  }
  return isSafe;
}