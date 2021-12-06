#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

#define PI 3.14159265

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

    bool operator==(const Point& other) const {
        return m_x == other.m_x && m_y == other.m_y;
    }

    bool operator==(const Point& other) {
        return m_x == other.m_x && m_y == other.m_y;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& d);
};

std::ostream& operator<<(std::ostream& out, const Point& d) {
    out << d.m_x << "," << d.m_y;
    return out;
}


class Segment {
public:
    Point m_start;
    Point m_end;

    Segment(Point start, Point end) {
        m_start = start;
        m_end = end;
    }

    bool vertical() {
        return m_start.m_x == m_end.m_x;
    }

    bool horizontal() {
        return m_start.m_y == m_end.m_y;
    }

    friend std::ostream& operator<<(std::ostream& out, const Segment& d);
};

std::ostream& operator<<(std::ostream& out, const Segment& d) {
    out << d.m_start << " -> " << d.m_end;
    return out;
}

int exercise1(std::vector<Segment>& segments) {
        std::map<Point, int> matrix;

    for (auto& elem : segments) {
        if (elem.vertical()) {
            int min_y = std::min(elem.m_start.m_y, elem.m_end.m_y);
            int max_y = std::max(elem.m_start.m_y, elem.m_end.m_y);
            for (int i = min_y; i <= max_y; i++) {
                Point p = Point(elem.m_start.m_x, i);
                if (matrix.find(p) == matrix.end()) {
                    matrix.insert(std::pair<Point, int>(p, 1));
                } else {
                    matrix[p] += 1;
                }
            }
        } else if (elem.horizontal()) {
            int min_x = std::min(elem.m_start.m_x, elem.m_end.m_x);
            int max_x = std::max(elem.m_start.m_x, elem.m_end.m_x);
            for (int i = min_x; i <= max_x; i++) {
                Point p = Point(i, elem.m_start.m_y);
                if (matrix.find(p) == matrix.end()) {
                    matrix.insert(std::pair<Point, int>(p, 1));
                } else {
                    matrix[p] += 1;
                }
            }
        }
    }

    int overlaps = 0;
    for(const auto& elem : matrix) {
        if(elem.second >= 2) {
            overlaps++;
        }
    }

    return overlaps;
}

int exercise2(std::vector<Segment>& segments) {
        std::map<Point, int> matrix;

    for (auto& elem : segments) {
        if (elem.vertical()) {
            int min_y = std::min(elem.m_start.m_y, elem.m_end.m_y);
            int max_y = std::max(elem.m_start.m_y, elem.m_end.m_y);
            for (int i = min_y; i <= max_y; i++) {
                Point p = Point(elem.m_start.m_x, i);
                if (matrix.find(p) == matrix.end()) {
                    matrix.insert(std::pair<Point, int>(p, 1));
                } else {
                    matrix[p] += 1;
                }
            }
        } else if (elem.horizontal()) {
            int min_x = std::min(elem.m_start.m_x, elem.m_end.m_x);
            int max_x = std::max(elem.m_start.m_x, elem.m_end.m_x);
            for (int i = min_x; i <= max_x; i++) {
                Point p = Point(i, elem.m_start.m_y);
                if (matrix.find(p) == matrix.end()) {
                    matrix.insert(std::pair<Point, int>(p, 1));
                } else {
                    matrix[p] += 1;
                }
            }
        } else {
            Point min_point = std::min(elem.m_start, elem.m_end);
            Point max_point = std::max(elem.m_start, elem.m_end);
            double deltax = max_point.m_x - min_point.m_x;
            double deltay = max_point.m_y - min_point.m_y;
            int angle = atan2(deltay, deltax) * 180 / PI;
            //std::cout << min_point << " -> " << max_point << " angle " << angle << std::endl;
            if (std::abs(angle) == 45) {
                Point p = min_point;
                while (p <= max_point) {
                    if (matrix.find(p) == matrix.end()) {
                        matrix.insert(std::pair<Point, int>(p, 1));
                    } else {
                        matrix[p] += 1;
                    }
                    p.m_x += 1;
                    p.m_y += (1 * sgn(angle));
                }
            }
        }
    }

    int overlaps = 0;
    for(const auto& elem : matrix) {
        if(elem.second >= 2) {
            overlaps++;
        }
    }

    return overlaps;
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

    std::vector<Segment> segments {};
    for (std::string v; std::getline(file, v);) {
        std::vector<std::string> tokens;
        split(v, " -> ", tokens);
        segments.push_back(Segment(Point(tokens[0]), Point(tokens[1])));
    }

    file.close();

    std::cout << "First exercise: " << exercise1(segments) << std::endl;
    std::cout << "Second exercise: " << exercise2(segments) << std::endl;

#ifdef DEBUG
#endif
    return 0;
}