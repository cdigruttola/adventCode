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

int getPriority(char c) {
    if (c >= 'a') {
        return c - 96;
    } else {
        return c - 38;
    }
}

int main(int argc, char *argv[]) {
    // Read input

    std::ifstream file;
    file.open("input.txt");

    if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector <std::string> input{};
    std::vector <std::string> firstHalf{};
    std::vector <std::string> secondHalf{};
    std::cout << "Loading file...\n";

    for (std::string v; std::getline(file, v);) {
        int half = v.size() / 2;
        firstHalf.push_back(v.substr(0, half));
        secondHalf.push_back(v.substr(half));
        input.push_back(v);
    }
    file.close();

    std::cout << "File loaded - rows count " << input.size() << "\n";

    long firstPriority = 0;
    for (int i = 0; i < firstHalf.size(); i++) {
        for (char c: firstHalf[i]) {
            if (secondHalf[i].find(c) != std::string::npos) {
                firstPriority += getPriority(c);
                break;
            }
        }
    }

    std::cout << "First exercise: " << firstPriority << std::endl;

    long secondPriority = 0;
    for (int i = 0; i < input.size() - 2; i += 3) {
        for (char c: input[i]) {
            if (input[i + 1].find(c) != std::string::npos && input[i + 2].find(c) != std::string::npos) {
                secondPriority += getPriority(c);
                break;
            }
        }
    }

    std::cout << "Second exercise: " << secondPriority << std::endl;

    return 0;
}