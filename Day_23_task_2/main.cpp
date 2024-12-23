#include <cinttypes>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>


int main() {
  std::unordered_map<int, std::set<int>> links;

  std::ifstream inputFS("./input");
  if (!inputFS.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return 1;
  }

  std::string line;

  while (std::getline(inputFS, line)) {
    if (line.empty()) {
      continue;
    }
    char a, b, c, d;
    sscanf(line.c_str(), "%c%c-%c%c", &a, &b, &c, &d);

    uint16_t p1 = (a << 8) + b;
    uint16_t p2 = (c << 8) + d;

    links[p2].insert(p1);
    links[p1].insert(p2);
  }
  inputFS.close();


  int count = 0;
  for (const auto& [k, v] : links) {
    if (v.size() >= 2) {
      for (const auto& s : v) {
        for (const auto& s1 : links[s]) {
          if (s1 == k) {
            continue;
          }
          if (links[s1].contains(k)) {
            if ((k>>8) == 't' || (s>>8) == 't' || (s1>>8) == 't') {
              count++;
            }
          }
        }
      }
    }
  }
  
  size_t best = 0;
  std::set<int> best_comp;

  for (auto [k, v] : links) {
    v.emplace(k);
    std::set<int> comb(v.begin(), v.end());
    for (const auto& ele : v) {
      if (!comb.contains(ele)) {
        continue;
      }
      auto tmp = links[ele];
      tmp.emplace(ele);

      std::vector<int> inter, tmp2;
      std::set_intersection(v.begin(), v.end(), tmp.begin(), tmp.end(),
                            std::back_inserter(inter));
      std::sort(inter.begin(), inter.end());
      std::set_intersection(inter.begin(), inter.end(), comb.begin(),
                            comb.end(), std::back_inserter(tmp2));
      comb.clear();
      comb.insert(tmp2.begin(), tmp2.end());
    }
    if (comb.size() > best) {
      best = comb.size();
      best_comp.clear();
      best_comp.insert(comb.begin(), comb.end());
    }
  }
  
  for (const auto& ele : best_comp) {
    char a = (ele >> 8) & 0xFF;
    char b = ele & 0xFF;
    std::cout << a << b << ",";
  }
  std::cout << std::endl;

  return 0;
}
