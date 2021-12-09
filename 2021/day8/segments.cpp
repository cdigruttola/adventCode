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

#define N 10
#define M 4

template<auto... ts, typename T>
constexpr auto isInList(const T &t) {
    return ((t == ts) || ...);
}

std::string intersection(std::string& v1, std::string& v2) {
    std::string v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));
    return v3;
}


template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

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

void split(std::string s, std::string delimiter, std::vector<int>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(stoi(s.substr(0, pos)));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(stoi(s));
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
#ifdef DEBUG
    file.open("test.txt");
#else
    file.open("input.txt");
#endif
	if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector<std::vector<std::string>> input {};
    std::vector<std::vector<std::string>> output {};
    for (std::string v; std::getline(file, v);) {
        std::stringstream ss(v);
        std::vector<std::string> line_input {};
        std::vector<std::string> line_output {};
        for (int i = 0; i < N; i++) {
            std::string a;
            ss >> a;
            line_input.push_back(a);
        }
        input.push_back(line_input);
        char pipe;
        ss >> pipe;
        for (int i = 0; i < M; i++) {
            std::string a;
            ss >> a;
            line_output.push_back(a);
        }
        output.push_back(line_output);
    }

    file.close();

    int count = 0;
    int32_t sum = 0;
    for (int i = 0; i < input.size(); i++) {
        std::array<std::string, N> decoded_input {};
        std::sort(input[i].begin(), input[i].end(), [](std::string& a, std::string& b)
                  {
                      return a.size() < b.size();
                  });
        decoded_input[1] = input[i][0];
        decoded_input[7] = input[i][1];
        decoded_input[4] = input[i][2];
        decoded_input[8] = input[i][9];
        for (int j = 3; j < 6; j++) {
            auto v = intersection(decoded_input[7], input[i][j]);
            if (v.size() == 3) {
                decoded_input[3] = input[i][j];
            } else if (v.size() == 2) {
                auto v1 = intersection(decoded_input[4], input[i][j]);
                if (v1.size() == 3) {
                    decoded_input[5] = input[i][j];
                } else {
                    decoded_input[2] = input[i][j];
                }
            }
        }
        for (int j = 6; j < 9; j++) {
            auto v = intersection(decoded_input[5], input[i][j]);
            if (v.size() == 5) {
                auto v1 = intersection(decoded_input[4], input[i][j]);
                if (v1.size() == 4) {
                    decoded_input[9] = input[i][j];
                } else {
                    decoded_input[6] = input[i][j];
                }
            } else {
                decoded_input[0] = input[i][j];
            }
        }
        for (auto& elem : decoded_input) {
            std::sort(elem.begin(), elem.end());
        }

        std::stringstream ss;
        for (auto& elem : output[i]) {
            if(isInList<2, 3, 4, 7>(elem.length())) {
                count++;
            }
            std::sort(elem.begin(), elem.end());
            auto it = std::find(decoded_input.begin(), decoded_input.end(), elem);
            if(it != decoded_input.end()) {
                int index = it - decoded_input.begin();
                ss << index;
            }
        }
        sum += stoi(ss.str());
    }

    std::cout << "First exercise: " << count << std::endl;
    std::cout << "Second exercise: " << sum << std::endl;

#ifdef DEBUG
    for (int i = 0; i < input.size(); i++) {
        for (auto& elem : input[i]) {
            std::cout << elem << " ";
        }
        std::cout << "| ";
        for (auto& elem : output[i]) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
#endif
    return 0;
}
