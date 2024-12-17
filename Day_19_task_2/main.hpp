#ifndef MAIN_HPP
#define MAIN_HPP
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

void loadData(const std::string &filename, std::set<std::string> &flags, std::vector<std::string> &patterns);

#endif // MAIN_HPP