#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

#define N 5

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

class Cell {
public:
    int m_number;
    bool m_marked;

    Cell() {}

    Cell(int number, bool marked = false) {
        m_number = number;
        m_marked = marked;
    }

    friend std::ostream& operator<<(std::ostream& out, const Cell& d);
};

std::ostream& operator<<(std::ostream& out, const Cell& d) {
    if(d.m_marked) {
        out << "\033[1;32m" << left_pad(std::to_string(d.m_number), 2, ' ') << "\033[0m";
    } else {
        out << left_pad(std::to_string(d.m_number), 2, ' ');
    }
    return out;
}

class Board {
public:
    Cell cells[N][N] {};
    int hitRows[N] {};
    int hitCols[N] {};
    bool bingo = false;

    Board() {
    }

    int sumNonHits() {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (!cells[i][j].m_marked) {
                    sum += cells[i][j].m_number;
                }
            }
        }
        return sum;
    }

    bool checkBingo() {
        for (int i = 0; i < N; i++) {
            if (hitRows[i] == N) {
                bingo = true;
                return true;
            }
            if (hitCols[i] == N) {
                bingo = true;
                return true;
            }
        }
        return false;
    }

    void markIfPresent(int n) {
        bool flag = false;
        for (int i = 0; i < N && !flag; i++) {
            for (int j = 0; j < N && !flag; j++) {
                if (!cells[i][j].m_marked && cells[i][j].m_number == n) {
                    cells[i][j].m_marked = true;
                    flag = true;
                    hitRows[i]++;
                    hitCols[j]++;
                    break;
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Board& d);
};

std::ostream& operator<<(std::ostream& out, const Board& d) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            out << d.cells[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
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

    std::vector<int> draws {};
    std::vector<Board> boards {};
    std::cout << "Loading file...\n";

    std::string v;
    std::getline(file, v);
    split(v, ",", draws);
    int row = 0;
    for (v; std::getline(file, v);) {
        if (v.size() < 2) {
            boards.push_back(Board());
            row = 0;
        } else {
            Board& b = boards.back();
            std::stringstream ss(v);
            for (int i = 0; i < N; i++) {
                int a;
                ss >> a;
                b.cells[row][i] = Cell(a);
            }
            row++;
        }
    }

    file.close();

    bool bingo = false;
    for (auto& n : draws) {
        if (bingo) {
            break;
        }
        for (auto& elem : boards) {
            elem.markIfPresent(n);
            if (elem.checkBingo()) {
                bingo = true;
                std::cout << "First exercise: " << elem.sumNonHits() * n << std::endl;
                break;
            }
        }
    }

    int allBingo = 0;
    Board lastBoard;
    int lastNumber;
    for (auto& n : draws) {
        if (allBingo == boards.size()) {
            break;
        }
        for (auto& elem : boards) {
            if (elem.bingo) {
                continue;
            }
            elem.markIfPresent(n);
            if (elem.checkBingo()) {
                allBingo++;
                lastNumber = n;
                lastBoard = elem;
            }
        }
    }
    std::cout << "Second exercise: " << lastBoard.sumNonHits() * lastNumber << std::endl;

#ifdef DEBUG
    for (auto& elem : draws) {
        std::cout << elem << ",";
    }
    std::cout << std::endl << std::endl;
    for (auto& elem : boards) {
        std::cout << elem << std::endl;
    }
#endif
    return 0;
}