#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <regex>

std::string SHINY_GOLD_BAG = "shiny gold";
const std::string NO_OTHER_BAGS = "no other";

void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
}

class Bag {
public:
	enum class Contains {
		YES,
		NO,
		DUNNO
	};
	
	std::string m_type;
	std::map<std::string, int> m_rules;
	Contains m_contains;

	Bag() = default;
	Bag(std::string type) : m_type(type), m_contains(Contains::DUNNO) {
	}

	void setType(const std::string &type) {
		m_type = type;
	}

	void addRule(const std::string &type, int count) {
        m_rules[type] = count;
    }

    void setContains(Contains value) {
    	m_contains = value;
    }

    Contains getContains() {
    	return m_contains;
    }

};

void getBags(std::vector<std::string>& lines, std::map<std::string, Bag>& bags) {
	std::string type;
	for (auto& str : lines) {
		bool empty = str.find(NO_OTHER_BAGS) != std::string::npos;
		std::stringstream ss(str);
        ss >> type; // aggettivo
        ss >> str;	// colore
        type += " " + str;
		bags[type] = Bag(type);
        if (empty) {
            continue;
        }
        Bag& currentBag = bags[type];
        ss >> str; // bags
        ss >> str; // contain
        int count;
        while (str != "bags." && str != "bag.") {
            ss >> count;
            ss >> type;
            ss >> str;
            type += " " + str;
            currentBag.addRule(type, count);
            ss >> str; // bags
        }
	}
}

void findBagsThatContain(std::string type, std::map<std::string, Bag>& bags, std::string investigated) {
	if (bags[investigated].getContains() != Bag::Contains::DUNNO) {
        return;
	}
    Bag &curBag = bags[investigated];
    for (const auto &rule : curBag.m_rules) {
        if (rule.first == type) {
            curBag.setContains(Bag::Contains::YES);
            break;
        }
        findBagsThatContain(type, bags, rule.first);
        if (bags[rule.first].getContains() == Bag::Contains::YES ) {
            curBag.setContains(Bag::Contains::YES);
            break;
        }
    }
    if (bags[investigated].getContains() == Bag::Contains::DUNNO) {
        bags[investigated].setContains(Bag::Contains::NO);
    }
}

void findBagsThatContain(std::string type, std::map<std::string, Bag>& bags, std::set<std::string>& ret) {
	for (auto& entry : bags) {
		findBagsThatContain(type, bags, entry.first);
		if(entry.second.getContains() == Bag::Contains::YES) {
			ret.insert(entry.first);
		}
	}
}

int bagsRequired(std::string type, std::map<std::string, Bag>& bags) {
	int required = 0;
	for (auto& entry : bags[type].m_rules) {
		required += entry.second + entry.second * bagsRequired(entry.first, bags);
	}
	return required;
}

int main() {
    // Read input

    std::ifstream file("day7.txt");
    std::vector<std::string> luggageLines{};
    
    for (std::string v; std::getline(file, v);) {
        luggageLines.push_back(v);
    }

    file.close();

    std::map<std::string, Bag> bags;
    std::string type;

    getBags(luggageLines, bags);
    std::set<std::string> ret{};
    findBagsThatContain(SHINY_GOLD_BAG, bags, ret);
    std::cout << ret.size() << "\n";
    std::cout << bagsRequired(SHINY_GOLD_BAG, bags) << "\n";
}
