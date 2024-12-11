#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>

using valueType = std::uint64_t;
void printData(const std::map<valueType, valueType> &data);
void processData(std::map<valueType, valueType> &data);
size_t countDigits(valueType value);

int main() {
  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::map<valueType, valueType> data;
  valueType currentValue;

  while (inputFS >> currentValue) {
    data[currentValue]++;
  }
  inputFS.close();
  printData(data);
  for (size_t i = 0; i < 75; i++) {
    processData(data);

    std::cout << "Step: "<< i <<  " Result: " << data.size() << std::endl;
  }

  size_t result = 0;
  for (auto& [k,v] : data) {
    result += v;
   // std::cout << k << "-" << v << " ";

  }
  std::cout << "Result: " << result << std::endl;

  return 0;
}

void printData(const std::map<valueType, valueType> &data) {
  for (auto& [k,v] : data) {
    std::cout << k << "-" << v << " ";
  }
  std::cout << std::endl;
}

void processData(std::map<valueType, valueType> &data) {
    std::map<valueType, valueType> newData;
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->first == 0) {
            newData[1]+=it->second;
        } else if (size_t digits = countDigits(it->first); digits % 2 == 0) {
          newData[it->first / std::pow(10, digits / 2)] += it->second;
          newData[it->first % static_cast<int>((std::pow(10, digits / 2)))] += it->second;
        } else {
          newData[it->first * 2024] += it->second;
        }
    }
    std::swap(data, newData);
}

size_t countDigits(valueType value) {
  size_t count = 0;
  while (value > 0) {
    value /= 10;
    count++;
  }
  return count;
}