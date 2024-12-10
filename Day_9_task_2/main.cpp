#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;
void printData(const std::list<std::pair<int, int>> &data);
void compactData(std::list<std::pair<int, int>> &data);
valueType calculateCheckSum(const std::list<std::pair<int, int>> &data);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::list<std::pair<int, int>>
      data;  //(fileNo, size), (-1, size) for freespace size
  char currentValue;
  bool isFile = true;
  int currentFileNumber = 0;

  while (inputFS >> currentValue) {
    if (isFile) {
      data.push_back(std::make_pair(currentFileNumber, currentValue - '0'));
      ++currentFileNumber;
    } else {
      data.push_back(std::make_pair(-1, currentValue - '0'));
    }
    isFile = !isFile;
  }
  inputFS.close();

  //printData(data);
  compactData(data);

  //std::cout << std::endl;
  //printData(data);
  std::cout << calculateCheckSum(data) << std::endl;
  return 0;
}

void printData(const std::list<std::pair<int, int>> &data) {
  for (auto i : data) {
    for (int j = 0; j < i.second; ++j) {
      if (i.first == -1) {
        std::cout << ".";
      } else {
        std::cout << i.first;
      }
    }
  }
  std::cout << std::endl;
}

void compactData(std::list<std::pair<int, int>> &data) {
  auto itRight = data.end();
  itRight--;
  while (itRight != data.begin()) {
    bool isFound = true;
    auto itLeft = data.begin();
    while (itLeft->first != -1) {
      ++itLeft;
      if (itLeft == itRight) {
        return;
      }
    }
    while (itRight->first == -1) {
      --itRight;
    }
    while (itRight->second > itLeft->second && itRight != data.begin()) {
      while ((itLeft->first != -1 || itRight->second > itLeft->second) &&
             itLeft != itRight && itLeft != data.end()) {
        ++itLeft;
      }
      if (itLeft == itRight) {
        --itRight;
        isFound = false;
      }
    }
    if (!isFound) {
      continue;
    }
    std::swap(itLeft->first, itRight->first);
    std::swap(itLeft->second, itRight->second);
    std::cout << std::endl;
    //printData(data);
    if (itLeft->second < itRight->second) {
      int newSize = itRight->second - itLeft->second;
      itRight->second = itLeft->second;
      itLeft++;
      data.insert(itLeft, std::make_pair(-1, newSize));
      itLeft--;
    }
    --itRight;
    //printData(data);
  }
}

valueType calculateCheckSum(const std::list<std::pair<int, int>> &data) {
  valueType checkSum = 0;
  size_t pos = 0;
  for (auto i : data) {
    size_t size = i.second;
    while (size > 0) {
      if (i.first != -1) {
        checkSum += i.first * pos;
      }
      ++pos;
      --size;
    }
  }
  return checkSum;
}