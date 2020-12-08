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

template<typename TK, typename TV>
std::vector<TK> extract_keys(std::map<TK, TV> const& input_map) {
  std::vector<TK> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.first);
  }
  return retval;
}

template<typename TK, typename TV>
std::vector<TV> extract_values(std::map<TK, TV> const& input_map) {
  std::vector<TV> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.second);
  }
  return retval;
}

class Passport {
public:
	std::map<std::string, std::string> props;

	Passport(std::vector<std::string>& v) {
		for (std::string s : v) {
			std::vector<std::string> tokens;
			split(s, " ", tokens);
			for (std::string token : tokens) {
    			std::string cod = token.substr(0, 3);
    			props.emplace(cod, token.substr(4));
    		}
    	}
	}

	bool isValidPart1() {
		std::vector<std::string> keys = extract_keys(props);
		if (keys.size() == 8 || (keys.size() == 7 && std::find(keys.begin(), keys.end(), "cid") == keys.end())) {
			return true;
		}
		return false;
	}

	bool isValidPart2() {
		std::cout << *this << "\n";
		std::vector<std::string> keys = extract_keys(props);
		if (keys.size() == 8 || (keys.size() == 7 && std::find(keys.begin(), keys.end(), "cid") == keys.end())) {
			std::regex fourDigitRegex("[0-9]{4}");
			// byr (Birth Year) - four digits; at least 1920 and at most 2002.
			std::string byr = props["byr"];
			if (!std::regex_match(byr, fourDigitRegex)) {
				return false;
			} else {
				int byrI = std::stoi(byr);
				if (byrI < 1920 || byrI > 2002) {
					return false;
				}
			}

			// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
			std::string iyr = props["iyr"];
			if (!std::regex_match(iyr, fourDigitRegex)) {
				return false;
			} else {
				int iyrI = std::stoi(iyr);
				if (iyrI < 2010 || iyrI > 2020) {
					return false;
				}
			}

			// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
			std::string eyr = props["eyr"];
			if (!std::regex_match(eyr, fourDigitRegex)) {
				return false;
			} else {
				int eyrI = std::stoi(eyr);
				if (eyrI < 2020 || eyrI > 2030) {
					return false;
				}
			}

			/* 
			hgt (Height) - a number followed by either cm or in:
				If cm, the number must be at least 150 and at most 193.
				If in, the number must be at least 59 and at most 76.*/
			std::string hgt = props["hgt"];
			size_t posIn = hgt.find("in");
			if (posIn != std::string::npos) {
        		hgt.erase(posIn);
        		int hgtI = std::stoi(hgt);
        		if (hgtI < 59 || hgtI > 76) {
        			return false;
        		}
    		} else {
    			posIn = hgt.find("cm");
    			if (posIn == std::string::npos) {
    				return false;
    			}
    			hgt.erase(posIn);
    			int hgtI = std::stoi(hgt);
        		if (hgtI < 150 || hgtI > 193) {
        			return false;
        		}
    		}

			// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
			std::regex hcl_regex("#[0-9abcdef]{6}");
			std::string hcl = props["hcl"];
			if (!std::regex_match(hcl, hcl_regex)) {
				return false;
			}

			// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
			std::string ecl = props["ecl"];
			if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" && ecl != "hzl" && ecl != "oth") {
				return false;
			}

			// pid (Passport ID) - a nine-digit number, including leading zeroes.
			std::string pid = props["pid"];
			std::regex pid_regex("[0-9]{9}");
			if (!std::regex_match(pid, pid_regex)) {
				return false;
			}
			return true;
		}
		return false;
	}


	friend std::ostream& operator<<(std::ostream& out, const Passport& p);

};

std::ostream& operator<<(std::ostream& out, const Passport& p) {
	for (const auto &pair : p.props) {
        out << pair.first << ":" << pair.second << " ";
    }
	return out;
}

int main() {
    // Read input

    std::ifstream file("day4.txt");
    std::vector<std::vector<std::string>> passport_lines{};
    std::vector<Passport> passportsParsed;
    
    for (std::string v; std::getline(file, v);) {
    	std::vector<std::string> passports{};
    	while (!v.empty()) {
    		passports.push_back(v);
			std::getline(file, v);
    	}
        passport_lines.push_back(passports);
        passports.clear();
    }

    file.close();

    for(std::vector<std::string> passports : passport_lines) {
    	passportsParsed.push_back(Passport(passports));
    }
    int valid1 = 0;
    int valid2 = 0;
    std::cout << "passports: " << passportsParsed.size() << "\n";
    for (Passport p : passportsParsed) {
    	if (p.isValidPart1()) {
    		valid1++;
    	}
    	if (p.isValidPart2()) {
    		valid2++;
    	}
    }
    std::cout << "Part 1: " << valid1 << "\n";
    std::cout << "Part 2: " << valid2 << "\n";
}