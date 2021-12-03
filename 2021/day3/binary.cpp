#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

void left_trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); }));
}

void right_trim(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(), str.end());
}

void trim(std::string& str) {
    left_trim(str);
    right_trim(str);
}


void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
}

std::string left_pad(std::string const& str, size_t size, char pad = '0') {
    if (str.size() < size)
        return std::string(size - str.size(), pad) + str;
    else
        return str;
    }

std::string right_pad(std::string const& str, size_t size, char pad = '0')
    {
        if (str.size() < size)
            return str + std::string(size - str.size(), pad);
        else
            return str;
    }

int main(int argc, char *argv[]) {
    // Read input

    std::ifstream file;
    file.open("input.txt");

	if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector<int> counts {};
    std::vector<std::string> oxygen {};
    std::vector<std::string> co2 {};
    int size;
    std::cout << "Loading file...\n";
    for (std::string v; std::getline(file, v);) {
        oxygen.push_back(v);
        co2.push_back(v);
        if (size == 0) {
            for (int i = 0; i < v.length() - 1; i++) {
                counts.push_back(((int)v[i] - 48));
            }
        } else {
            for (int i = 0; i < v.length() - 1; i++) {
                counts[i] += ((int)v[i] - 48);
            }
        }
        size++;
    }

    file.close();

    std::stringstream gamma_string;
    std::stringstream epsilon_string;
    for (auto& elem: counts) {
        if (elem > size / 2) {
            gamma_string << "1";
            epsilon_string << "0";
        } else {
            gamma_string << "0";
            epsilon_string << "1";
        }
    }

    int gamma = stoi(gamma_string.str(), 0, 2);
    int epsilon = stoi(epsilon_string.str(), 0, 2);

    std::cout << "First exercise: " << gamma * epsilon << std::endl;

    for (int i = 0; i < counts.size(); i++) {
        int countOxygen = 0;
        for (auto& elem : oxygen) {
            countOxygen += ((int)elem[i] - 48);
        }
        std::vector<std::string> oxygenToSave {};
        for (auto& elem : oxygen) {
            if (countOxygen >= oxygen.size() - countOxygen) {
                if (elem[i] == '1') {
                    oxygenToSave.push_back(elem);
                }
            } else {
                if (elem[i] == '0') {
                    oxygenToSave.push_back(elem);
                }
            }
        }
        oxygen = oxygenToSave;
    }

    for (int i = 0; i < counts.size(); i++) {
        int countCo2 = 0;
        for (auto& elem : co2) {
            countCo2 += ((int)elem[i] - 48);
        }
        std::vector<std::string> co2ToSave {};
        for (auto& elem : co2) {
            if (countCo2 >= co2.size() - countCo2) {
                if (elem[i] == '0') {
                    co2ToSave.push_back(elem);
                }
            } else {
                if (elem[i] == '1') {
                    co2ToSave.push_back(elem);
                }
            }
        }
        co2 = co2ToSave;
    }

    std::stringstream o2_s;
    o2_s << oxygen[0];
    int o2 = stoi(o2_s.str(), nullptr, 2);
    std::stringstream carbonDioxy_s;
    carbonDioxy_s << co2[0];
    int carbonDioxy = stoi(carbonDioxy_s.str(), nullptr, 2);
    std::cout << "Second exercise: " << o2 * carbonDioxy << std::endl;

    return 0;
}