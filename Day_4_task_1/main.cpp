#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::uint32_t countXMAS(const std::vector<std::string> &data, size_t i, size_t j);

int main() {
  std::ifstream inputFS("./input");

  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  // read from inputFS to vactor<std::string>
  std::vector<std::string> data;
  std::string line;
  while (std::getline(inputFS, line)) {
    data.push_back(line);
  }
  inputFS.close();

  std::uint32_t result = 0;

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data[i].size(); ++j) {
      if (data[i][j] == 'X') {
        result += countXMAS(data, i, j);
      }
    }
  }


  std::cout << result << std::endl;

  return 0;
}

std::uint32_t countXMAS(const std::vector<std::string> &data, size_t i, size_t j){
  std::uint32_t result = 0;
//to the left
if(j >= 3 && data[i][j-1] == 'M' && data[i][j-2] == 'A' && data[i][j-3] == 'S'){
  ++result;
}
//to the right
if(j < data[i].size()-3 && data[i][j+1] == 'M' && data[i][j+2] == 'A' && data[i][j+3] == 'S'){
  ++result;
}
//to the up
if(i >= 3 && data[i-1][j] == 'M' && data[i-2][j] == 'A' && data[i-3][j] == 'S'){
  ++result;
}
//to the down
if(i < data.size()-3 && data[i+1][j] == 'M' && data[i+2][j] == 'A' && data[i+3][j] == 'S'){
  ++result;
}
//to the up-left
if(i >= 3 && j >= 3 && data[i-1][j-1] == 'M' && data[i-2][j-2] == 'A' && data[i-3][j-3] == 'S'){
  ++result;
}
//to the up-right
if(i >= 3 && j < data[i].size()-3 && data[i-1][j+1] == 'M' && data[i-2][j+2] == 'A' && data[i-3][j+3] == 'S'){
  ++result;
}
//to the down-left
if(i < data.size()-3 && j >= 3 && data[i+1][j-1] == 'M' && data[i+2][j-2] == 'A' && data[i+3][j-3] == 'S'){
  ++result;
}
//to the down-right
if(i < data.size()-3 && j < data[i].size()-3 && data[i+1][j+1] == 'M' && data[i+2][j+2] == 'A' && data[i+3][j+3] == 'S'){
  ++result;
}

  return result;
}