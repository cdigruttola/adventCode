#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

bool is_low(std::vector<std::vector<int>>& input, int i, int j) {
    if (i < 0 || j < 0 || i >= input.size() || j >= input[0].size()) {
        return false;
    }
    int dir_x[] = {1, -1, 0, 0};
    int dir_y[] = {0, 0, 1, -1};
    if (input[i][j] == 9) {
        return false;
    }
    for (int k = 0; k < 4; k++) {
        int x = j + dir_x[k];
        int y = i + dir_y[k];
        if (x >= 0 && y >= 0 && y < input.size() && x < input[i].size() && input[y][x] <= input[i][j]) {
            return false;
        }
    }
    return true;
}

bool is_valid(std::vector<std::vector<int>>& input, int i, int j, std::vector<std::pair<int, int>>& visited) {
    if (i < 0 || j < 0 || i >= input.size() || j >= input[0].size()) {
        return false;
    }
    if (input[i][j] == 9) {
        return false;
    }
    if (std::find(visited.begin(), visited.end(), std::make_pair(i, j)) != visited.end()) {
        return false;
    }
    return true;
}

std::vector<std::pair<int, int>> find_lowest_positions(std::vector<std::vector<int>>& input) {
    std::vector<std::pair<int, int>> toReturn;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if(is_low(input, i, j)) {
                toReturn.emplace_back(i, j);
            }
        }
    }
    return toReturn;
}

int dfs(std::vector<std::vector<int>>& input, int i, int j, std::vector<std::pair<int, int>>& visited) {
    std::stack<std::pair<int, int>> st;
    st.emplace(i, j);
    int count = 0;
    while (!st.empty()) {
        auto curr = st.top();
        st.pop();
        if(is_valid(input, curr.first, curr.second, visited)) {
            count++;
            visited.emplace_back(curr.first, curr.second);
            st.emplace(curr.first - 1, curr.second);
            st.emplace(curr.first + 1, curr.second);
            st.emplace(curr.first, curr.second - 1);
            st.emplace(curr.first, curr.second + 1);
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    // Read input

    std::ifstream file;
#ifdef DEBUG
    file.open("test.txt");
#else
    file.open("input.txt");
#endif
	if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector<std::vector<int>> input {};
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        std::vector<int> v {};
        for (auto& c : s) {
            v.push_back(c - '0');
        }
        input.push_back(v);
    }
    file.close();   

    auto lowest_positions = find_lowest_positions(input);
    int sum = 0;
    for (auto& elem : lowest_positions) {
        sum += input[elem.first][elem.second] + 1;
    }

    std::vector<std::pair<int, int>> visited;
    std::vector<int> basinSize {};
    for (auto& elem : lowest_positions) {
        basinSize.push_back(dfs(input, elem.first, elem.second, visited));
    }
    std::sort(basinSize.begin(), basinSize.end(), [](int& a, int& b)
                  {
                      return a > b;
                  });    

    std::cout << "First exercise: " << sum << std::endl;
    std::cout << "Second exercise: " << basinSize[0] * basinSize[1] * basinSize[2] << std::endl;

#ifdef DEBUG
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (std::find(lowest_positions.begin(), lowest_positions.end(), std::make_pair(i, j)) != lowest_positions.end()) {
                std::cout << "\033[1;31m" << input[i][j] << "\033[0m";
            } else if (std::find(visited.begin(), visited.end(), std::make_pair(i, j)) != visited.end()) {
                std::cout << "\033[1;32m" << input[i][j] << "\033[0m";
            } else {
                std::cout << input[i][j];
            }
        }
        std::cout << std::endl;
    }
#endif
    return 0;
}
