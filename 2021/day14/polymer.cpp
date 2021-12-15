#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>
#include <thread>

void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
}

long solve(std::map<std::string, long>& pair_polymers, std::string& polymer_template) {
    std::map<char, long> m;
    for (auto& elem : pair_polymers) {
        if(m.find(elem.first[0]) == m.end()) {
            m[elem.first[0]] = elem.second;
        } else {
            m[elem.first[0]] += elem.second;
        }
    }
    m[polymer_template.back()]++;
    long min = std::numeric_limits<long>::max();
    long max = std::numeric_limits<long>::min();
    for (auto& elem : m) {
        min = std::min(min, elem.second);
        max = std::max(max, elem.second);
    }
    return max - min;
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

    std::map<std::string, long> pair_polymers {};
    std::string s, polymer_template;
    std::getline(file, s);
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    for (int i = 0; i < s.length() - 1; i++) {
        polymer_template = s;
        std::string key;
        key.append(1, s[i]).append(1, s[i + 1]);
        if(pair_polymers.find(key) == pair_polymers.end()) {
            pair_polymers[key] = 1;
        } else {
            pair_polymers[key]++;
        }
    }
    
    std::getline(file, s);
    std::map<std::string, char> rules {};
    for (s; std::getline(file, s);) {
        std::stringstream ss(s);
        std::string a, xx;
        char c;
        ss >> a >> xx >> c;
        rules[a] = c;
    }
    file.close();

    for (int i = 0; i < 40; i++) {
        std::map<std::string, long> new_pair_polymers {};
        for (auto& elem : pair_polymers) {
            if (rules.find(elem.first) != rules.end()) {
                std::string key_left;
                key_left.append(1, elem.first[0]).append(1, rules[elem.first]);
                std::string key_right;
                key_right.append(1, rules[elem.first]).append(1, elem.first[1]);
                if (new_pair_polymers.find(key_left) == new_pair_polymers.end()) {
                    new_pair_polymers[key_left] = elem.second;
                } else {
                    new_pair_polymers[key_left] += elem.second;
                }
                if (new_pair_polymers.find(key_right) == new_pair_polymers.end()) {
                    new_pair_polymers[key_right] = elem.second;
                } else {
                    new_pair_polymers[key_right] += elem.second;
                }
            }
        }
        pair_polymers = new_pair_polymers;
        if (i == 9) {
            std::cout << "First exercise: " << solve(pair_polymers, polymer_template) << std::endl;
        }
    }

    std::cout << "Second exercise: " << solve(pair_polymers, polymer_template) << std::endl;

#ifdef DEBUG
    for (auto& elem : pair_polymers) {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
#endif
    return 0;
}
