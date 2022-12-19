#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include <numeric>
#include <regex>

void left_trim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); }));
}

void right_trim(std::string &str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(), str.end());
}

void trim(std::string &str) {
    left_trim(str);
    right_trim(str);
}

void split(std::string s, std::string delimiter, std::vector<std::string> &tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
}

std::string left_pad(std::string const &str, size_t size, char pad = '0') {
    if (str.size() < size)
        return std::string(size - str.size(), pad) + str;
    else
        return str;
}

std::string right_pad(std::string const &str, size_t size, char pad = '0') {
    if (str.size() < size)
        return str + std::string(size - str.size(), pad);
    else
        return str;
}

int find_marker(std::string &line, int marker_size) {
    for (int i = 0; i < line.size() - marker_size; i++) {
        std::set<char> tmp;
        for (int j = 0; j < marker_size; j++) {
            tmp.insert(line[i + j]);
        }
        if (tmp.size() == marker_size) {
            return i + marker_size;
        }
        tmp.clear();
    }
    return -1;
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

    std::string line;
    std::cout << "Loading file...\n";
    std::getline(file, line);
    file.close();

    long firstPart = 0;

    std::cout << find_marker(line, 4) << std::endl;
    std::cout << find_marker(line, 14) << std::endl;

    return 0;
}
