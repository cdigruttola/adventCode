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

class Point {
public:
    int m_x;
    int m_y;

    Point() {}

    Point(int x, int y) : m_x(x), m_y(y) {}

    bool in_range(Point& min, Point& max) {
        return m_x >= min.m_x && m_x <= max.m_x && m_y >= min.m_y && m_y <= max.m_y;
    }
    // min (20, -10)
    // max (30, -5)
    // inizio da S(0, 0)
    // i è la mia velocità iniziale in x
    // j è la mia velocità iniziale in y
    bool move(Point& velocity, Point& min, Point& max) {
        bool found = false;
        while(!found && m_y >= min.m_y && m_x <= max.m_x) {
            if (in_range(min, max)) {
                found = true;
            }
            m_x += velocity.m_x > 0 ? velocity.m_x-- : 0; 
            m_y += velocity.m_y--;
        }
        return found;
    }
};

int part1 (int ymin) {
    return std::abs(ymin) * ((std::abs(ymin) - 1) / 2.0);
}

int part2 (Point& min, Point& max) {
    int count = 0;
    for (int i = 1; i <= max.m_x; i++) {
        for (int j = min.m_y; j < std::abs(min.m_y); j++) {
            Point initial(0, 0);
            Point velocity(i, j);
            if(initial.move(velocity, min, max)) {
                count++;
            }
        }
    }
    return count;
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

    Point targetmin;
    Point targetmax;
    std::cout << "Loading file...\n";
    for (std::string s; std::getline(file, s);) {
        //"target area: x=20..30, y=-10..-5";
        auto p1{s.find('=')};
        auto p2{s.find('.')};
        auto p3{s.find(',')};
        auto p4{s.rfind('=')};
        auto p5{s.rfind('.')};
        targetmin.m_x = std::stoi(s.substr(p1 + 1, p2 - p1 - 1));
        targetmax.m_x = std::stoi(s.substr(p2 + 2, p3 - p2 - 2));
        targetmin.m_y = std::stoi(s.substr(p4 + 1, p5 - p4 - 2));
        targetmax.m_y = std::stoi(s.substr(p5 + 1, s.size() - p5)); 
    }
    file.close();

    std::cout << "First exercise: " << part1(targetmin.m_y) << std::endl;
    std::cout << "First exercise: " << part2(targetmin, targetmax) << std::endl;
    return 0;
}