#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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


void split(std::string s, std::string delimiter, std::vector <std::string> &tokens) {
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

int main(int argc, char *argv[]) {
    // Read input

    std::ifstream file;
    file.open("input.txt");

    if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector <std::pair<char, char>> input{};
    std::cout << "Loading file...\n";

    for (std::string v; std::getline(file, v);) {
        std::vector <std::string> tokens;
        split(v, " ", tokens);
        input.push_back(std::make_pair(tokens[0][0], tokens[1][0]));
    }

    long firstScore = 0;
    long secondScore = 0;
    for (std::pair<char, char> elem: input) {
        switch (elem.second) {
            case 'X':
                if (elem.first == 'A') {
                    firstScore += 3;
                    secondScore += 3;
                } else if (elem.first == 'B') {
                    firstScore += 0;
                    secondScore += 1;
                } else if (elem.first == 'C') {
                    firstScore += 6;
                    secondScore += 2;
                }
                firstScore += 1;
                secondScore += 0;
                break;
            case 'Y':
                if (elem.first == 'A') {
                    firstScore += 6;
                    secondScore += 1;
                } else if (elem.first == 'B') {
                    firstScore += 3;
                    secondScore += 2;
                } else if (elem.first == 'C') {
                    firstScore += 0;
                    secondScore += 3;
                }
                firstScore += 2;
                secondScore += 3;
                break;
            case 'Z':
                if (elem.first == 'A') {
                    firstScore += 0;
                    secondScore += 2;
                } else if (elem.first == 'B') {
                    firstScore += 6;
                    secondScore += 3;
                } else if (elem.first == 'C') {
                    firstScore += 3;
                    secondScore += 1;
                }
                firstScore += 3;
                secondScore += 6;
                break;
        }
    }

    file.close();
    std::cout << "File loaded - rows count " << input.size() << "\n";

    std::cout << "First exercise: " << firstScore << std::endl;
    std::cout << "Second exercise: " << secondScore << std::endl;


    return 0;
}