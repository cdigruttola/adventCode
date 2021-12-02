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

class Direction {
public:
    std::string dir;
    int nr;

    Direction(std::vector<std::string>& v) {
        dir = v[0];
        nr = stoi(v[1]);
    }
};

int main(int argc, char *argv[]) {
    // Read input

    std::ifstream file;
    file.open("input.txt");

	if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector<Direction> input {};
    std::cout << "Loading file...\n";
    for (std::string v; std::getline(file, v);) {
        std::vector<std::string> tokens;
        split(v, " ", tokens);
        input.push_back(Direction(tokens));
    }
    file.close();
    std::cout << "File loaded - rows count " << input.size() << "\n";

    int horizontal = 0;
    int vertical = 0;
    int aim = 0;
    int depth = 0;
    for (auto& elem : input) {
        if (elem.dir == "up") {
            vertical -= elem.nr;
            aim -= elem.nr;
        } else if (elem.dir == "down") {
            vertical += elem.nr;
            aim += elem.nr;
        } else if (elem.dir == "forward") {
            horizontal += elem.nr;
            depth += aim * elem.nr;
        }
    }

    std::cout << "First exercise: " << horizontal * vertical << std::endl;

    std::cout << "Second exercise: " << horizontal * depth << std::endl;

    return 0;
}