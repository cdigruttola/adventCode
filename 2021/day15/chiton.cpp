#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include <regex>
#include <climits>

typedef std::pair<int, int> index_pair;

auto cmp = [](std::pair<index_pair, int> left, std::pair<index_pair, int> right) {
    return left.second > right.second; 
};

std::vector<index_pair> get_neighbours(index_pair& ij) {
    std::vector<index_pair> to_return;

    int dir_x[] = {1, -1, 0, 0};
    int dir_y[] = {0, 0, 1, -1};

    for (int k = 0; k < 4; k++) {
        int x = ij.first + dir_x[k];
        int y = ij.second + dir_y[k];
        to_return.push_back(std::make_pair(x, y));
    }
    return to_return;
}

bool is_inbound(std::vector<std::vector<int>>& graph, index_pair& ij) {
    return ij.first >= 0 && ij.second >= 0 && ij.first < graph.size() && ij.second < graph.size();
}

int dijkstra(std::vector<std::vector<int>>& graph) {
    std::priority_queue<std::pair<index_pair, int>, std::vector<std::pair<index_pair, int>>, decltype(cmp)> q(cmp);
    std::set<index_pair> visited;
    std::pair<int, int> start = std::make_pair(0, 0);
    std::pair<int, int> end = std::make_pair(graph.size() - 1, graph.size() - 1);
    q.emplace(start, 0);
    visited.emplace(start);

    while(!q.empty()) {
        auto elem = q.top();
        q.pop();
        if (elem.first == end) {
            return elem.second;
        }
        auto neighbours = get_neighbours(elem.first);
        for (auto neighbour : neighbours) {
            if(is_inbound(graph, neighbour) && visited.find(neighbour) == visited.end()) {
                q.emplace(neighbour, elem.second + graph[neighbour.first][neighbour.second]);
                visited.emplace(neighbour);
            }
        }
    }
    return 0;
}

void expand_matrix(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& expand) {
    for (int l = 0; l < 5; l++) {
        for (int k = 0; k < 5; k++) {
            for (int i = 0; i < graph.size(); i++) {
                for (int j = 0; j < graph.size(); j++) {
                    int v;
                    if (l == 0 && k == 0) {
                        v = graph[i][j];
                    } else {
                        v = graph[i][j] + k + l;
                        v = (v - 1) % 9 + 1;
                    }
                    expand[i + l * graph.size()][j + k * graph.size()] = v;
                }
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

    std::vector<std::vector<int>> input {};
    std::cout << "Loading file...\n";
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        std::vector<int> line {};
        for (auto& c : s) {
            line.push_back(c - '0');
        }
        input.push_back(line);
    }
    file.close();

    std::cout << "First exercise: " << dijkstra(input) << std::endl;
    std::vector<std::vector<int>> expand(input.size() * 5, std::vector<int>(input.size() * 5, 0));
    expand_matrix(input, expand);
    std::cout << "Second exercise: " <<  dijkstra(expand) << std::endl;

#ifdef DEBUG
    for (auto& line : input) {
        for (auto& c : line) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (auto& line : expand) {
        for (auto& c : line) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
#endif

    return 0;
}