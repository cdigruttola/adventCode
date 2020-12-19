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

class Bound {
public:
    int lower;
    int upper;

    Bound(std::string v) {
        std::vector<std::string> tokens;
        split(v, "-", tokens);
        lower = std::stoi(tokens[0]);
        upper = std::stoi(tokens[1]);
    }
};

class Rule {
public:

	std::string type;
    std::vector<Bound> bounds;
    std::vector<int> columns;

	Rule(std::string v) {
        std::vector<std::string> tokens;
        split(v, ": ", tokens);
		type = tokens[0];
        std::vector<std::string> tokensBound;
        split(tokens[1], " or ", tokensBound);
        bounds.push_back(Bound(tokensBound[0]));
        bounds.push_back(Bound(tokensBound[1]));
	}

    friend std::ostream& operator<<(std::ostream& out, const Rule& d);

    bool isValid(int t) {
        return t >= bounds[0].lower && t <= bounds[0].upper || t >= bounds[1].lower && t <= bounds[1].upper;
    }
};

std::ostream& operator<<(std::ostream& out, const Rule& d) {
    return out;
}

int main() {
    // Read input

#ifdef DEBUG
    std::ifstream rulesFile("rulesDebug.txt");
    std::ifstream nearbyTicketsFile("nearByTktDebug.txt");
#else
    std::ifstream rulesFile("rules.txt");
    std::ifstream nearbyTicketsFile("nearByTkt.txt");
#endif
    std::vector<Rule> rules;
    std::vector<int> myTickets = {89,179,173,167,157,127,163,113,137,109,151,131,97,149,107,83,79,139,59,53};
    std::vector<std::vector<int>> nearbyTickets;

    for (std::string v; std::getline(rulesFile, v);) {
    	rules.push_back(Rule(v));
    }
    rulesFile.close();
    
    for (std::string v; std::getline(nearbyTicketsFile, v);) {
        std::vector<std::string> tokens;
        split(v, ",", tokens);
        std::vector<int> inner;
        std::transform(tokens.begin(), tokens.end(), std::back_inserter(inner), [](std::string s) -> int { return std::stoi(s); });
        nearbyTickets.push_back(inner);
    }
    nearbyTicketsFile.close();

    std::vector<std::vector<int>> onlyNearbyValids;
    int invalid = 0;
    for (auto& ticket : nearbyTickets) {
        bool foundRuleValid = false;
        for (auto& t : ticket) {
            foundRuleValid = false;
            for (auto& rule : rules) {
                if (rule.isValid(t)) {
                    foundRuleValid = true;
                    break;
                }
            }
            if (!foundRuleValid) {
                invalid += t;
                break;
            }
        }
        if (foundRuleValid) {
            onlyNearbyValids.push_back(ticket);
        }
    }

    std::cout << invalid << "\n";

    for (auto& rule : rules) {
        for (int j = 0; j < onlyNearbyValids[0].size(); ++j) {
            bool foundRuleInvalid = false;
            for (int i = 0; i < onlyNearbyValids.size(); ++i) {
                if (!rule.isValid(onlyNearbyValids[i][j])) {
                    foundRuleInvalid = true;
                    break;
                }
            }
            if(!foundRuleInvalid) {
                rule.columns.push_back(j);
            }
        }
    }

    std::sort(rules.begin(), rules.end(), [](Rule a, Rule b) {
        return a.columns.size() < b.columns.size();   
    });

    for (int i = 0; i < rules.size(); ++i) {
        for (int j = i + 1; j < rules.size(); ++j) {
            auto find = std::find(rules[j].columns.begin(), rules[j].columns.end(), rules[i].columns[0]);
            rules[j].columns.erase(find, find + 1);
        }
    }

    long mul = 1;
    for (auto& rule : rules) {
        if (rule.type.find("departure") != std::string::npos) {
            mul *= myTickets[rule.columns[0]];
        }
    }

    std::cout << mul << "\n";
}