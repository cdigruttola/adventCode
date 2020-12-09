#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

int main() {
    // Read input

    std::ifstream file("day1.txt");
    
    std::string v;
    std::getline(file, v);
    file.close();

    int floor = 0;
    bool firstTimeBasement = true;
    for(int i = 0; i < v.length(); ++i) {
    	if (v[i] == '(') {
    		floor++;
    	} else if (v[i] == ')') {
    		floor--;
    	}
    	if (floor == -1 && firstTimeBasement) {
    		std::cout << (i + 1) << "\n";
    		firstTimeBasement = false;
    	}
    }

    std::cout << floor << "\n";

}