#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <regex>

const int preamble = 25;

long long findWeakness(std::vector<long long> numbers) {
	long long weakness = 0;
	for (int i = preamble; i < numbers.size(); ++i) {
		bool foundCorrect = false;
		for (int first = 0; first < preamble; ++first) {
			for (int second = 0; second < preamble; ++second) {
				if (numbers[i] == (numbers[first + i - preamble] + numbers[second + i - preamble])) {
					foundCorrect = true;
					break;
				}
			}
		}
		if (!foundCorrect) {
			weakness = numbers[i];
			break;
		}
	}
	return weakness;
}

std::set<long long> findSubset(std::vector<long long> numbers, long long weakness) {
	std::set<long long> subset{};
	long long sum = 0;
	bool found = false;
	for (int i = 0; i < numbers.size() && !found; ++i) {
		for (int j = i; j < numbers.size() && !found; ++j) {
			sum += numbers[j];
			subset.insert(numbers[j]);
			if (sum == weakness) {
				found = true;
				break;
			} else if (sum > weakness) {
				sum = 0;
				subset.clear();
				break;
			}
		}
	}
	return subset;
}

int main() {
    // Read input

    std::ifstream file("day9.txt");
    std::vector<long long> numbers{};
    
    for (std::string v; std::getline(file, v);) {
        numbers.push_back(std::stoll(v));
    }
    file.close();

    long long weak = findWeakness(numbers);
    std::cout << weak << "\n";
    std::set<long long> subset = findSubset(numbers, weak);
    long long max = *(max_element(subset.begin(), subset.end()));
    long long min = *(min_element(subset.begin(), subset.end()));
    std::cout << (max + min) << "\n";
}