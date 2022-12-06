#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

void printSections(const std::pair<int, int> &firstSectionIds, const std::pair<int, int> &secondSectionIds);

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

class Section {
public:
    int begin;
    int end;

    bool contains(const Section &s) const {
        return (begin <= s.begin && end >= s.end);
    }

    bool overlaps(const Section &s) const {
        return !(end < s.begin || s.end < begin);
    }
};

class Pair {
public:
    Section s_left;
    Section s_right;

    bool fully_contains() const {
        return s_left.contains(s_right) || s_right.contains(s_left);
    }

    bool overlaps() const { return s_left.overlaps(s_right); }
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

    std::vector<Pair> input{};
    std::cout << "Loading file...\n";

    for (std::string v; std::getline(file, v);) {
        std::vector<std::string> tokens;
        split(v, ",", tokens);
        std::vector<std::string> first;
        split(tokens[0], "-", first);
        std::vector<std::string> second;
        split(tokens[1], "-", second);
        Section firstSection;
        firstSection.begin = std::stoi(first[0]);
        firstSection.end = std::stoi(first[1]);
        Section secondSection;
        secondSection.begin = std::stoi(second[0]);
        secondSection.end = std::stoi(second[1]);
        Pair p;
        p.s_left = firstSection;
        p.s_right = secondSection;
        input.push_back(p);
    }
    file.close();

    std::cout << "File loaded - rows count " << input.size() << "\n";

    long firstOverlaps = 0;
    for (auto &elem: input) {
        auto firstSection = elem.s_left;
        auto secondSection = elem.s_right;
        if (firstSection.contains(secondSection) || secondSection.contains(firstSection)) {
            firstOverlaps++;
        }
    }

    std::cout << "First exercise: " << firstOverlaps << std::endl;

    long secondOverlaps = 0;
    for (auto &elem: input) {
        auto firstSection = elem.s_left;
        auto secondSection = elem.s_right;
        if (firstSection.overlaps(secondSection) || secondSection.overlaps(firstSection)) {
            secondOverlaps++;
        }
    }

    std::cout << "Second exercise: " << secondOverlaps << std::endl;

    return 0;
}
