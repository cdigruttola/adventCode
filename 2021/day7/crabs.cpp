#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <climits>

std::pair<int, int> solve(std::vector<int>& crabs, bool first) {
    auto max = *(std::max_element(crabs.begin(), crabs.end()));
    auto min = *(std::min_element(crabs.begin(), crabs.end()));
    std::map<int, std::vector<int>> fuel {};
    int min_fuel = INT_MAX;
    int min_fuel_pos = -1;
    for (int i = min; i < max; i++) {
        int sum_fuel = 0;
        for (auto& elem : crabs) {
            int distance = std::abs(elem - i);
            if (first) {
                sum_fuel += distance;
            } else {
                sum_fuel += (distance * (distance + 1) / 2);
            }
        }
        if (sum_fuel < min_fuel) {
            min_fuel = sum_fuel;
            min_fuel_pos = i;
        }
    }
    return std::make_pair(min_fuel, min_fuel_pos);
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

    std::vector<int> crabs {};
    for (std::string v; std::getline(file, v, ',');) {
        crabs.push_back(stoi(v));
    }

    file.close();

    auto min_fuel_first = solve(crabs, true);
    std::cout << "First exercise: fuel consumption " << min_fuel_first.first << ", position " << min_fuel_first.second << std::endl;
    auto min_fuel_second = solve(crabs, false);
    std::cout << "Second exercise: fuel consumption " << min_fuel_second.first << ", position " << min_fuel_second.second << std::endl;

    return 0;
}