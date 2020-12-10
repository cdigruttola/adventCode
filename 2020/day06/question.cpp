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

class Group {
public:
	std::map<char, int> question;
	int groupSize;

	Group(std::vector<std::string>& v) {
		groupSize = v.size();
		for (std::string s : v) {
			for (char c : s) {
				question[c] += 1;
			}
    	}
	}

	int countingKeys() {
		auto keys = extract_keys(question);
		return keys.size();
	}

	int countingPart2() {
		if (groupSize == 1) {
			return countingKeys();
		} else {
			int count = 0;
			for (auto& elem : question) {
				if (elem.second == groupSize) {
					count++;
				}
			}
			return count;
		}
	}

};

int main() {
    // Read input

    std::ifstream file("day6.txt");
    std::vector<std::vector<std::string>> questionsLines{};
    
    for (std::string v; std::getline(file, v);) {
    	std::vector<std::string> questions{};
    	while (!v.empty()) {
    		questions.push_back(v);
			std::getline(file, v);
    	}
        questionsLines.push_back(questions);
        questions.clear();
    }

    file.close();
    std::vector<Group> groups;
    for (std::vector<std::string> questions : questionsLines) {
    	groups.push_back(Group(questions));
    }
    int sum1 = 0;
    int sum2 = 0;
    for (Group g : groups) {
    	sum1 +=  g.countingKeys();
    	sum2 += g.countingPart2();
    }
    std::cout << sum1 << "\n";
    std::cout << sum2 << "\n";
}