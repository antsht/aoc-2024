#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using valueType = std::uint64_t;

int main() {
  std::ifstream inputFS("./input_test");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  std::vector<int> data;
  data.reserve(1000);
  char currentValue;
  bool isFile = true;
  int currentFileNumber = 0;
  // read the data from the file containing one line of numbers as single chars
  // and convert it to a vector of integers
 



  while (inputFS >> currentValue) {
    if(isFile){
      for (int i = 0; i < currentValue-'0'; i++) {
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

  for (auto i : data) {
    if(i==-1){
    std::cout << '.';} else {
    std::cout << i;
    }
  }

  return 0;
  }
