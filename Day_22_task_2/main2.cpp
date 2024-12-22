// THIS IS OPTIMIZED BY CHATGPT VERSION OF NAIN.CPP
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <tuple>
#include <vector>

uint64_t generateNextSecretNumber(uint64_t prevNumber) {
  u_int64_t nextNumber = (prevNumber ^ (prevNumber << 6)) % 16777216;
  nextNumber = (nextNumber ^ (nextNumber >> 5)) % 16777216;
  nextNumber = (nextNumber ^ (nextNumber << 11)) % 16777216;

  return nextNumber;
}

bool checkDiffSequence(const std::vector<int>& differences, int i,
                       const std::tuple<int, int, int, int>& diffSequence) {
  if (i < 3) return false;
  return (differences[i] == std::get<3>(diffSequence) &&
          differences[i - 1] == std::get<2>(diffSequence) &&
          differences[i - 2] == std::get<1>(diffSequence) &&
          differences[i - 3] == std::get<0>(diffSequence));
}

void processCombination(int i1, int i2_min, int i2_max,
                        const std::vector<uint64_t>& secretNumbers,
                        const std::tuple<int, int, int, int>& baseDiffSequence,
                        uint64_t& maxSum, std::mutex& mtx) {
  uint64_t localMaxSum = 0;
  std::vector<int> differences(2000);

  for (int i2 = i2_min; i2 <= i2_max; ++i2) {
    for (int i3 = std::max(-9, -9 + std::abs(i1 + i2));
         i3 <= std::min(9, 9 - std::abs(i1 + i2)); ++i3) {
      for (int i4 = std::max(-9, -9 + std::abs(i1 + i2 + i3));
           i4 <= std::min(9, 9 - std::abs(i1 + i2 + i3)); ++i4) {
        auto diffSequence = std::make_tuple(i1, i2, i3, i4);

        uint64_t sum = 0;
        for (auto number : secretNumbers) {
          int oldPrice = number % 10;

          for (int i = 0; i < 2000; ++i) {
            number = generateNextSecretNumber(number);
            int newPrice = number % 10;
            differences[i] = newPrice - oldPrice;
            oldPrice = newPrice;

            if (checkDiffSequence(differences, i, diffSequence)) {
              sum += newPrice;
              break;
            }
          }
        }

        localMaxSum = std::max(localMaxSum, sum);
      }
    }
  }

  std::lock_guard<std::mutex> lock(mtx);
  maxSum = std::max(maxSum, localMaxSum);
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
  const int MIN_DIGIT = -9;
  const int MAX_DIGIT = 9;

  std::mutex mtx;
  std::vector<std::thread> threads;

  for (int i1 = MIN_DIGIT; i1 <= MAX_DIGIT; ++i1) {
    int i2_min = std::max(MIN_DIGIT, -9 + std::abs(i1));
    int i2_max = std::min(MAX_DIGIT, 9 - std::abs(i1));

    threads.emplace_back(processCombination, i1, i2_min, i2_max,
                         std::cref(secretNumbers), std::make_tuple(0, 0, 0, 0),
                         std::ref(maxSum), std::ref(mtx));
  }

  for (auto& t : threads) {
    if (t.joinable()) t.join();
  }

  std::cout << "Max sum: " << maxSum << std::endl;
  return 0;
}
