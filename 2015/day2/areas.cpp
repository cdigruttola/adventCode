#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>

void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
}

class Size {
public:
	int w;
	int l;
	int h;

	Size(std::string s) {
		std::vector<std::string> tokens;
		split(s, "x", tokens);
		l = std::stoi(tokens[0]);
		w = std::stoi(tokens[1]);
		h = std::stoi(tokens[2]);
	}

	int findMinArea() {
		std::vector<int> v { l*w, w*h, h*l };
		return *(min_element(v.begin(), v.end()));
	}

	int calculateArea() {
		return 2*l*w + 2*w*h + 2*h*l + findMinArea();
	}

	std::pair<int, int> find2Mins() {
		std::vector<int> v { l, w, h };
		std::sort(v.begin(), v.end());
		return std::make_pair(v[0], v[1]);
	}

	int calculateRibbon() {
		auto val = find2Mins();
		return 2*val.first + 2*val.second + l*w*h;
	}

	friend std::ostream& operator<<(std::ostream& out, const Size& p);
};

std::ostream& operator<<(std::ostream& out, const Size& p) {
    out << "l " << p.l << " w " << p.w << " h " << p.h;
	return out;
}

int main() {
    // Read input

    std::ifstream file("day2.txt");
    std::vector<Size> sizes{};
    
    for (std::string v; std::getline(file, v);) {
        sizes.push_back(Size(v));
    }

    file.close();

    long area = 0;
    long ribbon = 0;
    for (auto& size : sizes) {
    	area += size.calculateArea();
    	ribbon += size.calculateRibbon();
    }

    std::cout << area << "\n";
    std::cout << ribbon << "\n";

}