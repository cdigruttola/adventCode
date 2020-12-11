#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int countOccupiedAdjacentTolerance(std::vector<std::string>& seats, int row, int col) {
	int count = 0;
	// top
	for (int i = row - 1; i >= 0 && seats[i][col] != 'L'; --i) {
		if (seats[i][col] == '#') {
			count++;
			break;
		}
	}
	// bottom
	for (int i = row + 1; i < seats.size() && seats[i][col] != 'L'; ++i) {
		if (seats[i][col] == '#') {
			count++;
			break;
		}
	}
	// right
	for (int j = col + 1; j < seats[row].length() && seats[row][j] != 'L'; ++j) {
		if (seats[row][j] == '#') {
			count++;
			break;
		}
	}
	// left
	for (int j = col - 1; j >= 0 && seats[row][j] != 'L'; --j) {
		if (seats[row][j] == '#') {
			count++;
			break;
		}
	}
	// top right
	for (int i = row - 1, j = col + 1; i >= 0 && j < seats[row].length() && seats[i][j] != 'L'; --i, ++j) {
		if (seats[i][j] == '#') {
			count++;
			break;
		}
	}
	// top left
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0 && seats[i][j] != 'L'; --i, --j) {
		if (seats[i][j] == '#') {
			count++;
			break;
		}
	}
	// bottom right
	for (int i = row + 1, j = col + 1; i < seats.size() && j < seats[row].length() && seats[i][j] != 'L'; ++i, ++j) {
		if (seats[i][j] == '#') {
			count++;
			break;
		}
	}
	// bottom left
	for (int i = row + 1, j = col - 1; i < seats.size() && j >= 0 && seats[i][j] != 'L'; ++i, --j) {
		if (seats[i][j] == '#') {
			count++;
			break;
		}
	}
	return count;
}

int countOccupiedAdjacent(std::vector<std::string>& seats, int row, int col) {
	int count = 0;
	// top
	if (row - 1 >= 0 && seats[row - 1][col] == '#') {
		count++;
	}
	// bottom
	if (row + 1 < seats.size() && seats[row + 1][col] == '#') {
		count++;
	}
	// right
	if (col + 1 < seats[row].length() && seats[row][col + 1] == '#') {
		count++;
	}
	// left
	if (col - 1 >= 0 && seats[row][col - 1] == '#') {
		count++;
	}
	// top right
	if (row - 1 >= 0 && col + 1 < seats[row].length() && seats[row - 1][col + 1] == '#') {
		count++;
	}
	// top left
	if (row - 1 >= 0 && col - 1 >= 0 && seats[row - 1][col - 1] == '#') {
		count++;
	}
	// bottom right
	if (row + 1 < seats.size() && col + 1 < seats[row].length() && seats[row + 1][col + 1] == '#') {
		count++;
	}
	// bottom left
	if (row + 1 < seats.size() && col - 1 >= 0 && seats[row + 1][col - 1] == '#') {
		count++;
	}	
	return count;
}

int countSeats(std::vector<std::string> seats) {
	std::vector<std::string> current = seats;
	bool changed;
	int occupied = 0;
	do {
		changed = false;
		for (int i = 0; i< seats.size(); ++i) {
			for (int j = 0; j < seats[i].length(); ++j) {
				if (seats[i][j] == 'L' && countOccupiedAdjacent(seats, i, j) == 0) {
					current[i][j] = '#';
					changed = true;
					++occupied;
				} else if (seats[i][j] == '#' && countOccupiedAdjacent(seats, i, j) >= 4) {
					current[i][j] = 'L';
					changed = true;
					--occupied;
				}
			}
		}
		seats = current;
#ifdef DEBUG
		for (std::string x : current) {
			std::cout << x << "\n";
		}
	std::cout << std::endl;
#endif
	} while (changed);
	return occupied;
}

int countSeatsTolerance(std::vector<std::string> seats) {
	std::vector<std::string> current = seats;
	bool changed;
	int occupied = 0;
	do {
		changed = false;
		for (int i = 0; i< seats.size(); ++i) {
			for (int j = 0; j < seats[i].length(); ++j) {
				if (seats[i][j] == 'L' && countOccupiedAdjacentTolerance(seats, i, j) == 0) {
					current[i][j] = '#';
					changed = true;
					++occupied;
				} else if (seats[i][j] == '#' && countOccupiedAdjacentTolerance(seats, i, j) >= 5) {
					current[i][j] = 'L';
					changed = true;
					--occupied;
				}
			}
		}
		seats = current;
#ifdef DEBUG
		for (std::string x : current) {
			std::cout << x << "\n";
		}
	std::cout << std::endl;
#endif
	} while (changed);
	return occupied;
}

int main() {
    // Read input
#ifdef DEBUG
	std::ifstream file("debug.txt");
#else
    std::ifstream file("day11.txt");
#endif
    std::vector<std::string> seats{};
    
    for (std::string v; std::getline(file, v);) {
        seats.push_back(v);
    }
    file.close();

    std::cout << countSeats(seats) << "\n";
    std::cout << countSeatsTolerance(seats) << "\n";
}