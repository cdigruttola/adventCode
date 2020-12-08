#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
}

int main() {
    // Read input

    std::ifstream file("day2.txt");
    std::vector<std::string> password_lines{};
    
    for (std::string v; std::getline(file, v);) {
        password_lines.push_back(v);
    }

    file.close();

    int firstFounded = 0;
    int secondPartFounded = 0;
    for (std::string s : password_lines) {
        std::vector<std::string> tokens;
        split(s, " ", tokens);
        // tokens[0] -> x-y
        // token[1] -> c:
        // token[2] -> password
        std::vector<std::string> limits;
        split(tokens[0], "-", limits);
        int firstLimit = std::stoi(limits[0]);
        int lastLimit = std::stoi(limits[1]);
        char c = tokens[1][0];
        int count = std::count(tokens[2].begin(), tokens[2].end(), c);
        if (count >= firstLimit && count <= lastLimit) {
            firstFounded++;
        }
        if ((tokens[2][firstLimit - 1] == c && tokens[2][lastLimit - 1] != c) || (tokens[2][firstLimit - 1] != c && tokens[2][lastLimit - 1] == c)) {
            secondPartFounded++;
        }

    }
    std::cout<< firstFounded << "\n";
    std::cout<< secondPartFounded << "\n";
}