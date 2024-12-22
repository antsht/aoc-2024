#include "main.hpp"

bool checkDiffSequence(std::vector<int> differences, int i,
                       std::tuple<int, int, int, int> &diffSequence) {
  if (i < 4) return false;
  if (differences[i] == std::get<3>(diffSequence) &&
      differences[i - 1] == std::get<2>(diffSequence) &&
      differences[i - 2] == std::get<1>(diffSequence) &&
      differences[i - 3] == std::get<0>(diffSequence)) {
    return true;
  }
  return false;
}

int main() {
  std::vector<uint64_t> secretNumbers;
  secretNumbers.reserve(2008);

  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }
  uint64_t a;
  while (inputFS >> a) {
    secretNumbers.emplace_back(a);
  }
  inputFS.close();
  uint64_t maxSum = 0;
  std::tuple<int, int, int, int> diffSequence{-2, 1, -1, 3};
  const int MIN_DIGIT = -9;
  const int MAX_DIGIT = 9;

  for (int i1 = MIN_DIGIT; i1 <= MAX_DIGIT; ++i1) {
    int i2_min = std::max(MIN_DIGIT, -9 + std::abs(i1));
    int i2_max = std::min(MAX_DIGIT, 9 - std::abs(i1));
    std::cout << "i1: " << i1 << std::endl;
    for (int i2 = i2_min; i2 <= i2_max; ++i2) {
      int i3_min = std::max(MIN_DIGIT, -9 + std::abs(i1 + i2));
      int i3_max = std::min(MAX_DIGIT, 9 - std::abs(i1 + i2));
      for (int i3 = i3_min; i3 <= i3_max; ++i3) {
        int i4_min = std::max(MIN_DIGIT, -9 + std::abs(i1 + i2 + i3));
        int i4_max = std::min(MAX_DIGIT, 9 - std::abs(i1 + i2 + i3));
        for (int i4 = i4_min; i4 <= i4_max; ++i4) {
          std::get<0>(diffSequence) = i1;
          std::get<1>(diffSequence) = i2;
          std::get<2>(diffSequence) = i3;
          std::get<3>(diffSequence) = i4;

          uint64_t sum = 0;
          for (auto number : secretNumbers) {

            std::vector<int> differences;
            differences.reserve(2000);
            // std::cout << "Init number: " << number << std::endl;
            for (size_t i = 0; i < 2000; ++i) {
              int oldPrice = number % 10;
              number = generateNextSecretNumber(number);
              int newPrice = number % 10;
              differences.emplace_back(newPrice - oldPrice);

              if (checkDiffSequence(differences, i, diffSequence)) {
                /* std::cout << "Diff sequence: " << std::get<0>(diffSequence)
                 <<
                 "
                 "
                           << std::get<1>(diffSequence) << " "
                           << std::get<2>(diffSequence) << " "
                           << std::get<3>(diffSequence) << std::endl;
                 std::cout << "New price: " << newPrice << std::endl;*/
                sum += newPrice;
                break;
              }
            }
          }
          // std::cout << "Sum: " << sum << std::endl;
          if (sum > maxSum) {
            maxSum = sum;
          }
        }
      }
    }
  }
  std::cout << "Max sum: " << maxSum << std::endl;
  return 0;
}

uint64_t generateNextSecretNumber(uint64_t prevNumber) {
  u_int64_t nextNumber = (prevNumber ^ (prevNumber << 6)) % 16777216;
  nextNumber = (nextNumber ^ (nextNumber >> 5)) % 16777216;
  nextNumber = (nextNumber ^ (nextNumber << 11)) % 16777216;

  return nextNumber;
}