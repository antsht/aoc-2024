#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

int main() {
    std::vector<int> leftColumn;
    std::vector<int> rightColumn;
    leftColumn.reserve(1000);
    leftColumn.reserve(1000);

    std::ifstream inputFS("input");
    
    if (inputFS.is_open()) {
        int left, right;
        while (inputFS >> left >> right) {
            leftColumn.push_back(left);
            rightColumn.push_back(right);
        }
    } else {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }
    std::sort(leftColumn.begin(), leftColumn.end());
    std::sort(rightColumn.begin(), rightColumn.end());

    u_int64_t result = 0;
    for (size_t i = 0; i < leftColumn.size(); ++i) {
        result += std::abs(leftColumn[i] - rightColumn[i]);
    }

    std::cout << result << std::endl;

    return 0;
}