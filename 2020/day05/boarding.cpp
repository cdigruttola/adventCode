#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <cmath>

void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
}

template<typename TK, typename TV>
std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
  std::vector<TK> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.first);
  }
  return retval;
}

template<typename TK, typename TV>
std::vector<TV> extract_values(std::map<TK, TV> const& input_map) {
  std::vector<TV> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.second);
  }
  return retval;
}

int main() {
    // Read input

    std::ifstream file("day5.txt");
    std::vector<std::string> boarding_lines{};
    
    for (std::string v; std::getline(file, v);) {
        boarding_lines.push_back(v);
    }
    file.close();

    std::vector<int> seatIds{};
    for (std::string s : boarding_lines) {
    int row [2] = { 0, 127 };
    int column [2] = { 0, 7 };
    	for (char const &c: s) {
    		if (c == 'F') {
    			row[1] = row[1] - ceil((row[1] - row[0]) / 2.0);
    		} else if (c == 'B') {
    			row[0] = row[0] + ceil((row[1] - row[0]) / 2.0);
    		} 
    		if (c == 'L') {
    			column[1] = column[1] - ceil((column[1] - column[0]) / 2.0);
    		} else if (c == 'R') {
    			column[0] = column[0] + ceil((column[1] - column[0]) / 2.0);
    		}
    	}
    	seatIds.push_back(row[0] * 8 + column[0]);
    }
    int max = *(max_element(seatIds.begin(), seatIds.end()));
    std::cout << max << "\n";
    std::sort(seatIds.begin(), seatIds.end());
    int yourSeat = 0;
    int currId = 0;
    for (int i : seatIds) {
    	if (i - currId > 1) {
    		yourSeat = i - 1;
    	}
    	currId = i;
    }
    std::cout << yourSeat << "\n";
}