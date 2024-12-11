#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <list>

using valueType = std::uint64_t;
void printData(const std::list<valueType> &data);
void processData(const std::list<valueType> &data);


int main() {
  std::ifstream inputFS("./input_test");
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

  return 0;
}

void printData(const std::list<valueType> &data) {
  for (auto i : data) {
      std::cout << i << " ";
  }
  std::cout << std::endl;
}

void processData(const std::list<valueType> &data) {
  for (auto i : data) {
      if (i==0){i=1;} else if (){} else {i*=2024;}
  }
  std::cout << std::endl;
}

