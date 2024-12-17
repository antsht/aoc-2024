#ifndef MAIN_HPP
#define MAIN_HPP
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>

void loadData(const std::string &filename, std::vector<std::string> &flags, std::vector<std::string> &patterns);
uint64_t countWaysToMakeWord(const std::string &word,
                            const std::vector<std::string> &tokens);
#endif  // MAIN_HPP