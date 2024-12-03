#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::ifstream inputFS("./input");

  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  std::string content((std::istreambuf_iterator<char>(inputFS)),
                      std::istreambuf_iterator<char>());
  inputFS.close();

  std::regex pattern(R"(mul\((\d+),(\d+)\))"); 
  std::smatch match;
  std::uint32_t result = 0;

  std::string::const_iterator searchStart(content.cbegin());
  while (std::regex_search(searchStart, content.cend(), match, pattern)) {
    int x = std::stoi(match[1].str());
    int y = std::stoi(match[2].str());
    result += x * y;
    searchStart = match.suffix().first;
  }

  std::cout << result << std::endl;

  return 0;
}

