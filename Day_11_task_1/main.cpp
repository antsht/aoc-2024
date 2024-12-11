#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

using valueType = std::uint64_t;
void printData(const std::list<valueType> &data);
void processData(std::list<valueType> &data);
size_t countDigits(valueType value);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::list<valueType> data;
  valueType currentValue;

  while (inputFS >> currentValue) {
    data.push_back(currentValue);
  }
  inputFS.close();
  printData(data);
  for (size_t i = 0; i < 25; i++) {
    processData(data);
  }
    
    std::cout << "Result: " << data.size() << std::endl;

  return 0;
}

void printData(const std::list<valueType> &data) {
  for (auto i : data) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

void processData(std::list<valueType> &data) {
  for (auto it = data.begin(); it != data.end(); ++it) {
    if (*it == 0) {
      *it = 1;
    } else if (size_t digits = countDigits(*it); digits % 2 == 0) {
      data.insert(it, (*it) / std::pow(10, digits / 2));
      *it = *it % static_cast<int>((std::pow(10, digits / 2)));

    } else {
      *it *= 2024;
    }
  }
}

size_t countDigits(valueType value) {
  size_t count = 0;
  while (value > 0) {
    value /= 10;
    count++;
  }
  return count;
}