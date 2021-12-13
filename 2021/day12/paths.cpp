#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <map>
#include <set>
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

bool is_upper(std::string& s) {
    for (auto& c : s) {
        if (islower(c)) {
            return false;
        }
    }
    return true;
}

void walk(std::string node, std::map<std::string, std::vector<std::string>>& graph, std::vector<std::string> path, std::set<std::string> visited, std::vector<std::vector<std::string>>& paths, bool part1 = true, bool revisit_small = false) {
    path.push_back(node);
    if (node == "end") {
        paths.push_back(path);
        return;
    }
    if (!is_upper(node)) {
        visited.insert(node);
    }

    for(auto& s : graph[node]) {
        if (part1) {
            if (visited.find(s) == visited.end()) {
                walk(s, graph, path, visited, paths, part1);
            }
        } else {
            if (visited.find(s) == visited.end()) {
                walk(s, graph, path, visited, paths, part1, revisit_small);
            } else if (!revisit_small && s != "start") {
                walk(s, graph, path, visited, paths, part1, true);
            }
        }
    }
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

    std::map<std::string, std::vector<std::string>> graph {};
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        std::vector<std::string> tokens;
        split(s, "-", tokens);
        graph[tokens[0]].push_back(tokens[1]);
        graph[tokens[1]].push_back(tokens[0]);
    }
    file.close();
    std::vector<std::vector<std::string>> paths1;
    walk("start", graph, std::vector<std::string>{}, std::set<std::string>(), paths1);
    
    std::vector<std::vector<std::string>> paths2;
    walk("start", graph, std::vector<std::string>{}, std::set<std::string>(), paths2, false);

    std::cout << "First exercise: " << paths1.size() << std::endl;
    std::cout << "Second exercise: " << paths2.size() << std::endl;
#ifdef DEBUG
    std::cout << "Part 1" << std::endl;
    for (auto& path : paths1) {
        for (auto& node : path) {
            std::cout << node << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "Part 2" << std::endl;
    for (auto& path : paths2) {
        for (auto& node : path) {
            std::cout << node << "\t";
        }
        std::cout << std::endl;
    }
#endif
    return 0;
}
