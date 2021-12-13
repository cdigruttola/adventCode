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

class Point {
public:
    int m_x;
    int m_y;

    Point() {
        m_x = -1;
        m_y = -1;
    }

    Point(int x, int y) {
        m_x = x;
        m_y = y;
    }

    Point(std::string s) {
        std::vector<std::string> tokens;
        split(s, ",", tokens);
        m_x = stoi(tokens[0]);
        m_y = stoi(tokens[1]);
    }

    Point(const Point &p1) {
        m_x = p1.m_x;
        m_y = p1.m_y;
    }

    bool operator<(const Point& rhs) const {
        return (m_x < rhs.m_x) || ((m_x == rhs.m_x) && (m_y < rhs.m_y));
    }

    bool operator<(const Point& rhs) {
        return (m_x < rhs.m_x) || ((m_x == rhs.m_x) && (m_y < rhs.m_y));
    }

    bool operator<=(const Point& rhs) const {
        return (m_x <= rhs.m_x) || ((m_x == rhs.m_x) && (m_y <= rhs.m_y));
    }

    bool operator<=(const Point& rhs) {
        return (m_x <= rhs.m_x) || ((m_x == rhs.m_x) && (m_y <= rhs.m_y));
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& d);
};

std::ostream& operator<<(std::ostream& out, const Point& d) {
    out << d.m_x << "," << d.m_y;
    return out;
}

class Instruction {
public:
    std::string m_dir;
    int m_position;

    Instruction(std::string dir, int position) {
        m_dir = dir;
        m_position = position;
    }

    Instruction(std::string s) {
            std::vector<std::string> tokens;
            split(s, "=", tokens);
            m_dir = tokens[0].back();
            m_position = stoi(tokens[1]);
    }

    friend std::ostream& operator<<(std::ostream& out, const Instruction& d);
};

std::ostream& operator<<(std::ostream& out, const Instruction& d) {
    out << "fold along " << d.m_dir << "=" << d.m_position;
    return out;
}

void fold(Instruction instruction, std::set<Point>& points) {
    std::set<Point> res;
    for (auto& elem : points) {
        if (instruction.m_dir == "x") {
            if (elem.m_x < instruction.m_position) {
                res.insert(elem);
            } else {
                res.insert(Point(instruction.m_position * 2 - elem.m_x, elem.m_y));
            }
        } else {
            if (elem.m_y < instruction.m_position) {
                res.insert(elem);
            } else {
                res.insert(Point(elem.m_x, instruction.m_position * 2 - elem.m_y));
            }
        }
    }
    points.clear();
    points = res;
}

void print(std::set<Point>& points) {
    int max_x = -1;
    int max_y = -1;
    for (auto& elem : points) {
        if (elem.m_x > max_x) {
            max_x = elem.m_x;
        }
        if (elem.m_y > max_y) {
            max_y = elem.m_y;
        }
    }
    std::cout << "max x " << max_x << " max y " << max_y << std::endl;
    for (int i = 0; i <= max_y; i++) {
        for (int j = 0; j <= max_x; j++) {
            Point p(j, i);
            if(points.find(p) == points.end()) {
                std::cout << ".";
            }
            else {
                std::cout << "#";
            }
        }
        std::cout << std::endl;
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

    std::set<Point> points {};
    std::vector<Instruction> instructions {};
    bool start_instructions = false;
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        if(s.empty()) {
            start_instructions = true;
        } else if (!start_instructions) {
            points.insert(Point(s));
        } else {
            instructions.push_back(Instruction(s));
        }
    }
    file.close();

    //print(points);
    bool first = true;
    for (auto& elem : instructions) {
        fold(elem, points);
        if (first) {
            std::cout << "First exercise: " << points.size() << std::endl;
            first = false;
        }
    }
    print(points);
    return 0;
}
