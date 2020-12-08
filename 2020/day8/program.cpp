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

class Instruction {
public:
	std::string ins;
	int number;
	bool executed;

	Instruction() {
	}

	Instruction(std::string instruction) : executed(false) {
		std::vector<std::string> tokens;
		split(instruction, " ", tokens);
		ins = tokens[0];
		number = std::stoi(tokens[1]);
	}

	Instruction(const Instruction& other) {
		ins = other.ins;
		number = other.number;
		executed = false;
	}

	std::string getInstruction() {
		return ins;
	}

	void setInstruction(std::string newIns) {
		ins = newIns;
	}

	int getNumber() {
		return number;
	}

	void setExecuted(bool exec) {
		executed = exec;
	}

	bool isExecuted() {
		return executed;
	}

	friend std::ostream& operator<<(std::ostream& out, const Instruction& p);

	bool operator==(const Instruction& other) {
		return ins == other.ins && number == other.number;
	}
};

std::ostream& operator<<(std::ostream& out, const Instruction& p) {
	out << p.ins << " " << p.number << " ";
	return out;
}

bool execute(std::vector<Instruction>& program, int& accumulator) {
    int i = 0;
    for (i; i < program.size();) {
		Instruction& ins = program[i];
		if (ins.isExecuted()) {
			return false;
		}
		ins.setExecuted(true);
		if (ins.getInstruction() == "nop") {
			++i;
		}
		if (ins.getInstruction() == "acc") {
			accumulator += ins.getNumber();
			++i;
		}
		if (ins.getInstruction() == "jmp") {
			i += ins.getNumber();
		}
	}
	return true;
}

int main() {
    // Read input

    std::ifstream file("day8.txt");
    std::vector<Instruction> program{};
    
    for (std::string v; std::getline(file, v);) {
        program.push_back(Instruction(v));
    }

    file.close();

    int accumulator = 0;
    execute(program, accumulator);
    std::cout << accumulator << "\n";

    for (int i = 0; i < program.size(); ++i) {
    	std::vector<Instruction> cpyInput{};
		for (int j = 0; j < program.size(); ++j) {
			cpyInput.push_back(program[j]);
		}
    	int result = 0;
    	bool isTerminated;
		if (program[i].getInstruction() == "nop") {
			Instruction& ins = cpyInput[i];
			ins.setInstruction("jmp");
            isTerminated = execute(cpyInput, result);
        } else if (program[i].getInstruction() == "jmp") {
			Instruction& ins = cpyInput[i];
			ins.setInstruction("nop");
	        isTerminated = execute(cpyInput, result);
	    }
	    if (isTerminated) {
	        std::cout << result << "\n";
	        break;
	    }
	}
}