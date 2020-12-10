#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

int part1(std::vector<int> joltages) {
	int diff1 = 0;
	int diff3 = 0;
	for (int i = 1; i < joltages.size(); ++i) {
		if (joltages[i] - joltages[i - 1] == 1) {
			diff1++;
		}
		if (joltages[i] - joltages[i - 1] == 3) {
			diff3++;
		}
	}
	return diff1 * diff3;
}

unsigned long long int part2(std::vector<int> joltages) {
	std::vector<unsigned long long int> v{};
	v.push_back(1);
	unsigned long long int first, second, third;
	for (int i = 1; i < joltages.size(); ++i) {
		if (i == 1) {
			if (joltages[i] - joltages[i - 1] <= 3) {
				v.push_back(v[0]);
			} else {
				v.push_back(0);
			}
		} else if (i == 2) {
			if (joltages[i] - joltages[i - 2] <= 3) {
				first = v[0];
			} else {
				first = 0;
			}
			if (joltages[i] - joltages[i - 1] <= 3) {
				second = v[1];
			} else {
				second = 0;
			}
			v.push_back(first + second);
		} else {
			if (joltages[i] - joltages[i - 3] <= 3) {
				first = v[i - 3];
			} else {
				first = 0;
			}
			if (joltages[i] - joltages[i - 2] <= 3) {
				second = v[i - 2];
			} else {
				second = 0;
			}
			if (joltages[i] - joltages[i - 1] <= 3) {
				third = v[i - 1];
			} else {
				third = 0;
			}
			v.push_back(first + second + third);
		}
	}
	for (unsigned long long int d : v) {
		std::cout << d << "\n";
	}
	return v[v.size() - 1];
}

int main() {
    // Read input

    std::ifstream file("day10.txt");
    std::vector<int> joltages{};
    joltages.push_back(0); // starting from 0 voltage
    for (std::string v; std::getline(file, v);) {
        joltages.push_back(std::stoi(v));
    }

    file.close();

    std::sort(joltages.begin(), joltages.end());
    joltages.push_back(joltages[joltages.size() - 1] + 3); // my adapter is 3 higher than the highest in vector

    std::cout << part1(joltages) << "\n";
    std::cout << part2(joltages) << "\n";
}