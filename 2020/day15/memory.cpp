#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> nums{ 6, 19, 0, 5, 7, 13, 1 }; 

int speak_sequence(int finalTurn) {
  std::unordered_map<int, int> lastSeen;
  int prev = nums[nums.size() - 1];

  for (int i = 0; i < nums.size(); i++) {
    lastSeen[nums[i]] = i;
  }

  for (int i = nums.size(); i < finalTurn; i++) {
    int curr;
    if (lastSeen.find(prev) == lastSeen.end()) {
      curr = 0;
    } else {
      curr = i - 1 - lastSeen[prev];
    }
    lastSeen[prev] = i - 1;
    prev = curr;
  }
  return prev;
}

int main() {
  std::cout << "Part 1\n" << speak_sequence(2020) << "\n";
  std::cout << "Part 2\n" << speak_sequence(30000000) << "\n";
  return 0;
}
