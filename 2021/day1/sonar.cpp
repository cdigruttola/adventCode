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

    std::vector<int> input {};
    std::cout << "Loading file...\n";
    for (std::string v; std::getline(file, v);) {
        input.push_back(std::stoi(v));
    }
    file.close();
    std::cout << "File loaded - rows count " << input.size() << "\n";

    int countIncreaseFirst = 0;
    for (int i = 1; i < input.size(); i++) {
        if (input[i] > input[i - 1]) {
            countIncreaseFirst++;
        }
    }
    std::cout << "First exercise: " << countIncreaseFirst << std::endl;

    int countIncreaseSecond = 0;
    for (int i = 3; i < input.size(); i++) {
        if (input[i] + input[i - 1] + input[i - 2] > input[i - 1] + input[i - 2] + input[i - 3]) {
            countIncreaseSecond++;
        }
    }
    std::cout << "Second exercise: " << countIncreaseSecond << std::endl;

    return 0;
}