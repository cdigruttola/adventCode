#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

class Chunk {
public:
    char m_opening = '.';
    int m_score = -1;

    Chunk() {}

    Chunk(char opening, int score) {
        m_opening = opening;
        m_score = score;
    }
};

std::map<char, Chunk> m = {{')', Chunk('(', 3)}, {']', Chunk('[', 57)}, {'}', Chunk('{', 1197)}, {'>', Chunk('<', 25137)}, 
{'(', Chunk(')', 1)}, {'[', Chunk(']', 2)}, {'{', Chunk('}', 3)}, {'<', Chunk('>', 4)}};

int solve1 (std::vector<std::string>& input) {
    long sum = 0;
    for (auto& elem : input) {
        std::stack<char> st;
        bool flag = false;
        for (int i = 0; i < elem.length() && ! flag; i++) {
            switch (elem[i]) {
                case '(':
                case '[':
                case '{':
                case '<':
                    st.emplace(elem[i]);
                break;
                default:
                    auto curr = st.top();
                    if (curr == m[elem[i]].m_opening) {
                        st.pop();
                    } else {
                        sum += m[elem[i]].m_score;
                        flag = true;
                    }
                break;
            }
        }
    }
    return sum;
}

long solve2 (std::vector<std::string>& input) {
    std::vector<long> scores {};
    for (auto& elem : input) {
        std::stack<char> st;
        bool flag = false;
        for (int i = 0; i < elem.length() && !flag; i++) {
            switch (elem[i]) {
                case '(':
                case '[':
                case '{':
                case '<':
                    st.emplace(elem[i]);
                break;
                default:
                    auto curr = st.top();
                    if (curr == m[elem[i]].m_opening) {
                        st.pop();
                    } else {
                        flag = true;
                    }
                break;
            }
        }
        if (!flag) {
            long score = 0;
            while(!st.empty()) {
                score = score * 5 + m[st.top()].m_score;
                st.pop();
            }
            scores.push_back(score);
        }
    }
    std::sort(scores.begin(), scores.end());
    return scores[scores.size() / 2];
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

    std::vector<std::string> input {};
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        input.push_back(s);
    }
    file.close();

    std::cout << "First exercise: " << solve1(input) << std::endl;
    std::cout << "Second exercise: " << solve2(input) << std::endl;

#ifdef DEBUG
#endif
    return 0;
}
