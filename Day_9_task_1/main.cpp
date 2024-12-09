#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;
void printData(const std::vector<int> &data);
valueType calculateCheckSum(const std::vector<int> &data);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<int> data;
  data.reserve(1000);
  char currentValue;
  bool isFile = true;
  int currentFileNumber = 0;

  while (inputFS >> currentValue) {
    if (isFile) {
      for (int i = 0; i < currentValue - '0'; i++) {
        data.push_back(currentFileNumber);
      }
      ++currentFileNumber;
    } else {
      for (int i = 0; i < currentValue - '0'; i++) {
        data.push_back(-1);
      }
    }
    isFile = !isFile;
  }
  inputFS.close();

  printData(data);

  auto itLeft = data.begin();
  auto itRight = data.end() - 1;
  while (*itRight == -1) {
    --itRight;
  }
  while (itLeft < itRight) {
    if (*itLeft == -1) {
      std::swap(*itLeft, *itRight);
      ++itLeft;
      while (*itRight == -1) {
        --itRight;
      }
      continue;
    }
    ++itLeft;
  }
  std::cout << std::endl;
  printData(data);
  std::cout << calculateCheckSum(data) << std::endl;
  return 0;
}

void printData(const std::vector<int> &data) {
  for (auto i : data) {
    if (i == -1) {
      std::cout << ".";
    } else {
      std::cout << i;
    }
  }
  std::cout << std::endl;
}

valueType calculateCheckSum(const std::vector<int> &data) {
  valueType checkSum = 0;
  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i] != -1) {
      checkSum += i * data[i];
    }
  }
  return checkSum;
}