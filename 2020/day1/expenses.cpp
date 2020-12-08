// 2 cicli for
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    // Read input

    std::ifstream file("day1.txt");
    std::vector<int> expense_lines{};
    
    for (std::string v; std::getline(file, v);) {
        expense_lines.push_back(std::stoi(v));
    }
    file.close();
    bool found = false;
    for (int i = 0; i < expense_lines.size() - 2 && !found; ++i) {
    	for (int j = i + 1; j < expense_lines.size() - 1 && !found; ++j) {
    		for( int k = j + 1; k < expense_lines.size() && !found; ++k) {
    			if (expense_lines[i] + expense_lines[j] + expense_lines[k] == 2020) {
    				std::cout << expense_lines[i] * expense_lines[j] * expense_lines[k] << "\n";
    				found = true;
    			}
    		}
    	}
    }
}