#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <regex>
#include <bitset>
#include <cmath>
#include <numeric>

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

std::unordered_map<long, unsigned long> allValuesPart1;
std::unordered_map<long, unsigned long> allValuesPart2;

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
		maskAnd = std::bitset<36>(tmpMaskAnd).to_ulong();
		maskOr = std::bitset<36>(tmpMaskOr).to_ulong();
		tokens.clear();
		for (int i = 1; i < v.size(); ++i) {
			split(v[i], "] = ", tokens);
			memory.push_back(std::make_pair(std::stol(tokens[0].substr(4)), std::stoul(tokens[1])));
			tokens.clear();
		}
	}

	void calculatePart1() {
		for (auto& elem : memory) {
			unsigned long value = maskAnd & elem.second;
			value = maskOr | value;
			allValuesPart1.insert_or_assign(elem.first, value);
		}
	}

	void calculatePart2() {
		auto xPos = getXPosition();
		std::reverse(xPos.begin(), xPos.end());
		for (auto& elem : memory) {
			unsigned long value = maskOr | elem.first;
			if (xPos.size() > 0) {
				std::string maskedAddress = std::bitset<36>(value).to_string();
				for (auto& pos : xPos) {
					maskedAddress[pos] = 'X';
				}
				writeFloating(maskedAddress, elem.second);
			} else {
				allValuesPart2.insert_or_assign(value, elem.second);
			}
		}
	}

    friend std::ostream& operator<<(std::ostream& out, const Mask& d);

private:

	std::vector<int> getXPosition() {
		std::vector<int> toReturn {};
		auto it = mask.begin();
		while ((it = std::find_if(it, mask.end(), [](char x){return x == 'X'; })) != mask.end()) {
			toReturn.push_back(std::distance(mask.begin(), it));
			it++;
		}
		return toReturn;
	}

	std::vector<unsigned long> addresses(std::string& maskedAddress, std::vector<int>& xPos) {
		std::vector<unsigned long> toReturn {};
		int dispositionWithRepetition = pow(2, xPos.size());		
		// std::cout << mask.length() - 1 - pos << "\n";
		return toReturn;
	}

	void writeFloating(std::string binAdr, unsigned long value) {
		// Get the index of any floating bits, if any
		size_t floatingIndex = binAdr.find("X");
		// If there are no more then this memory address is complete
		if (floatingIndex == std::string::npos) {
			// Convert the address to decimal and write the memory, then return
			allValuesPart2.insert_or_assign(std::bitset<36>(binAdr).to_ulong(), value);
			return;
		}
		// Set the address to 0 then recursively call writeFloating
		binAdr[floatingIndex] = '0';
		writeFloating(binAdr, value);
		// Set the address to 1 then recursively call writeFloating
		binAdr[floatingIndex] = '1';
		writeFloating(binAdr, value);
	}

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
    	elem.calculatePart1();
    	elem.calculatePart2();
    }

    unsigned long long sum1 = std::transform_reduce(allValuesPart1.begin(), allValuesPart1.end(), 0ul, std::plus{}, [](auto p) { return p.second; }); 
    unsigned long long sum2 = std::transform_reduce(allValuesPart2.begin(), allValuesPart2.end(), 0ul, std::plus{}, [](auto p) { return p.second; }); 

    std::cout << sum1 << "\n";
    std::cout << sum2 << "\n";
}