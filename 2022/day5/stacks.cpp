#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
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

class Instruction {
public:
    int move;
    int from;
    int to;

    void moveFunction1(std::vector<char> &fromVector, std::vector<char> &toVector) {
        for (int i = 0; i < move; i++) {
            toVector.push_back(fromVector.back());
            fromVector.pop_back();
        }
    }

    void moveFunction2(std::vector<char> &fromVector, std::vector<char> &toVector) {
        std::vector<char> tmp{};
        for (int i = 0; i < move; i++) {
            tmp.push_back(fromVector.back());
            fromVector.pop_back();
        }
        for (int i = 0; i < move; i++) {
            toVector.push_back(tmp.back());
            tmp.pop_back();
        }
    }
};

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

#ifdef DEBUG
    int numberOfStacks = 3;
#else
    int numberOfStacks = 9;
#endif
    std::vector<char> crates[numberOfStacks];
    std::vector<char> crates2[numberOfStacks];
    std::vector<Instruction> instructions{};

    std::cout << "Loading file...\n";

    for (std::string v; std::getline(file, v);) {
        if (v.substr(1, 1) == "1") {
            break;
        }
        for (int i = 0; i < numberOfStacks; i++) {
            if (v.substr(4 * i + 1, 1) == " ") {
                continue;
            }
            crates[i].push_back(v[4 * i + 1]);
            crates2[i].push_back(v[4 * i + 1]);
        }
    }

    for (std::string v; std::getline(file, v);) {
        trim(v);
        if (v.size() > 0) {
            std::stringstream ss(v);
            int move, from, to;
            std::string blank;
            ss >> blank >> move >> blank >> from >> blank >> to;
            Instruction i;
            i.move = move;
            i.from = from - 1;
            i.to = to - 1;
            instructions.push_back(i);

        }
    }
    file.close();

    for (size_t i = 0; i < numberOfStacks; i++) {
        std::reverse(crates[i].begin(), crates[i].end());
        std::reverse(crates2[i].begin(), crates2[i].end());
    }

    for (auto &elem: instructions) {
        elem.moveFunction1(crates[elem.from], crates[elem.to]);
        elem.moveFunction2(crates2[elem.from], crates2[elem.to]);
    }

    std::string firstPart = "";
    std::string secondPart = "";
    for (size_t i = 0; i < numberOfStacks; i++) {
        firstPart += crates[i].back();
        secondPart += crates2[i].back();
    }

    std::cout << "First exercise: " << firstPart << std::endl;
    std::cout << "Second exercise: " << secondPart << std::endl;

    return 0;
}
