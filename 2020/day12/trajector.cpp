#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

class Direction {
public:
	char dir;
	int number;

	Direction(std::string& s) {
		dir = s[0];
		number = std::stoi(s.substr(1));
	}

	friend std::ostream& operator<<(std::ostream& out, const Direction& d);
};

std::ostream& operator<<(std::ostream& out, const Direction& d) {
    out << d.dir << d.number;
	return out;
}

int manhattanDistance(std::vector<Direction>& directions) {
	int x = 0, y = 0;
	char currentDir = 'E';
	std::map<char, std::vector<char>> mapChange;
	std::vector<char> v = {'E', 'S', 'W'};
	mapChange.emplace('N', v);
	v = {'W', 'N', 'E'};
	mapChange.emplace('S', v);
	v = {'S', 'W', 'N'};
	mapChange.emplace('E', v);
	v = {'N', 'E', 'S'};	
	mapChange.emplace('W', v);
	for (Direction d : directions) {
		switch (d.dir) {
			case 'N': {
				y += d.number;
				break;
			}
			case 'S': {
				y -= d.number;
				break;
			}
			case 'W': {
				x -= d.number;
				break;
			}
			case 'E': {
				x += d.number;
				break;
			}
			case 'R': {
				int accessInMap = d.number / 90 - 1;
				currentDir = mapChange[currentDir][accessInMap];
				break;
			}
			case 'L': {
				int accessInMap = (360 - d.number) / 90 - 1;
				currentDir = mapChange[currentDir][accessInMap];
				break;
			}
			case 'F': {
				switch (currentDir) {
					case 'N': {
						y += d.number;
						break;
					}
					case 'S': {
						y -= d.number;
						break;
					}
					case 'W': {
						x -= d.number;
						break;
					}
					case 'E': {
						x += d.number;
						break;
					}
				}
				break;
			}
		}
	}
	return abs(x) + abs(y);
}

int waypointManhattanDistance(std::vector<Direction>& directions) {
	int x = 0, y = 0;
	int wy = 1, wx = 10;

	for (Direction d : directions) {
		switch (d.dir) {
			case 'N': {
				wy += d.number;
				break;
			}
			case 'S': {
				wy -= d.number;
				break;
			}
			case 'W': {
				wx -= d.number;
				break;
			}
			case 'E': {
				wx += d.number;
				break;
			}
			case 'L': {
				// 90
				if (d.number == 90) {
					int tmpw = wx;
					wx = -wy;
					wy = tmpw;
				}
				if (d.number == 180) {
					wx = -wx;
					wy = -wy;
				}
				if (d.number == 270) {
					int tmpw = wx;
					wx = wy;
					wy = -tmpw;
				}
				break;
			}
			case 'R': {
				if (d.number == 90) {
					int tmpw = wx;
					wx = wy;
					wy = -tmpw;
				}
				if (d.number == 180) {
					wx = -wx;
					wy = -wy;
				}
				if (d.number == 270) {
					int tmpw = wx;
					wx = -wy;
					wy = tmpw;
				}
				break;
			}
			case 'F': {
				x += wx * d.number;
				y += wy * d.number;
				break;
			}
		}
		//std::cout << "x " << x << " y " << y << " wx " << wx << " wy " << wy << "\n";
	}

	return abs(x) + abs(y);
}

int main() {
    // Read input
#ifdef DEBUG
    std::ifstream file("debug.txt");
#else
    std::ifstream file("day12.txt");
#endif    
    std::vector<Direction> directions{};
    
    for (std::string v; std::getline(file, v);) {
        directions.push_back(Direction(v));
    }

    file.close();
#ifdef DEBUG
    for (auto& d : directions) {
    	std::cout << d << "\n";
    }
#endif

    std::cout << manhattanDistance(directions) << "\n";
    std::cout << waypointManhattanDistance(directions) << "\n";

}