#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <regex>

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

std::string left_pad(std::string const& str, size_t size, char pad = '0') {
    if (str.size() < size)
        return std::string(size - str.size(), pad) + str;
    else
        return str;
    }

std::unordered_map<long, unsigned long> allValues;

class Mask {
public:
	std::string mask;
	unsigned long maskAnd;
	unsigned long maskOr;
	std::vector<std::pair<long, unsigned long>> memory;

	Mask(std::vector<std::string>& v) {
		std::vector<std::string> tokens;
		split(v[0], " = ", tokens);
		std::string tmpMaskAnd = tokens[1];
		std::string tmpMaskOr = tokens[1];
		mask = tokens[1];
		std::replace(tmpMaskAnd.begin(), tmpMaskAnd.end(), 'X', '1');
		std::replace(tmpMaskOr.begin(), tmpMaskOr.end(), 'X', '0');
		maskAnd = std::stoul(tmpMaskAnd, 0, 2);
		maskOr = std::stoul(tmpMaskOr, 0, 2);
		tokens.clear();
		for (int i = 1; i < v.size(); ++i) {
			split(v[i], "] = ", tokens);
			memory.push_back(std::make_pair(std::stol(tokens[0].substr(4)), std::stoul(tokens[1])));
			tokens.clear();
		}
	}

	void calculate() {
		for (auto& elem : memory) {
			unsigned long value = maskAnd & elem.second;
			value = maskOr | value;
			allValues.insert_or_assign(elem.first, value);
		}
	}

    friend std::ostream& operator<<(std::ostream& out, const Mask& d);
};

std::ostream& operator<<(std::ostream& out, const Mask& d) {
    out << "mask = " << d.mask << "\n";
    for (const auto& elem : d.memory) {
    	out << "mem[" << elem.first << "] = " << elem.second << "\n";
    }
    return out;
}


int main() {
    // Read input

    std::ifstream file("day14.txt");
    std::vector<Mask> masks;
    
    for (std::string v; std::getline(file, v);) {
    	std::vector<std::string> passports{};
    	while (!v.empty()) {
    		passports.push_back(v);
			std::getline(file, v);
    	}
        masks.push_back(Mask(passports));
        passports.clear();
    }
    file.close();

    for (auto& elem : masks) {
    	elem.calculate();
    }

    unsigned long long value = 0;
    for (auto& elem : allValues) {
    	value += elem.second;
    }

    std::cout << value << "\n";
}