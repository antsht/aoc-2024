#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

void removeSections(std::string& content);

int main() {
    std::ifstream inputFS("./input");

    if (!inputFS.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(inputFS)), std::istreambuf_iterator<char>());
    inputFS.close();

    removeSections(content);
    std::cout << content;
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

void removeSections(std::string& content) {
    size_t pos = 0;  // Start from the beginning of the string
    while ((pos = content.find("don't()", pos)) != std::string::npos) {
        size_t start_erase = pos;  // Record the position of "don't()"
        size_t pos_do = content.find(
            "do()", start_erase + 7);  // Search for "do()" after "don't()"

        if (pos_do != std::string::npos) {
          // Erase the section from "don't()" to the end of "do()"
          content.erase(start_erase, (pos_do + 4) - start_erase);
          // Continue searching from the current position
          pos = start_erase;
        } else {
          content.erase(start_erase);
          break;
        }
    }
}