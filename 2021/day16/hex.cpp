#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include <regex>
#include <climits>

#define TYPE_VERSION_BITS 3
#define LITERAL_GROUP_BITS 5

const std::string hex_char_to_bin(char c) {
    switch(c) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
    return "";
}

std::string hex_str_to_bin_str(const std::string& hex) {
    std::string bin;
    for(auto& c : hex)
       bin += hex_char_to_bin(c);
    return bin;
}

class Packet {
public:
    int m_version;
    int m_type;
    char m_type_id;
    long long m_value;
    std::vector<Packet> sub_packets;

    Packet() {}

    Packet(int version, int type) : m_version(version), m_type(type) {
        m_value = -1;
    }
};

Packet parse_packet(std::string& input, int& index) {
    int version = std::stoi(input.substr(index, TYPE_VERSION_BITS), 0, 2);
    index += TYPE_VERSION_BITS;
    int type = std::stoi(input.substr(index, TYPE_VERSION_BITS), 0, 2);
    index += TYPE_VERSION_BITS;

    Packet current_packet(version, type);

    if(type == 4) {
        std::stringstream binary_value;
        while(input[index] == '1') {
            binary_value << input.substr(index + 1, LITERAL_GROUP_BITS - 1);
            index += LITERAL_GROUP_BITS;
        }
        binary_value << input.substr(index + 1, LITERAL_GROUP_BITS - 1);
        index += LITERAL_GROUP_BITS;
        current_packet.m_value = std::stoll(binary_value.str(), 0, 2);
        return current_packet;
    } else {
        int len_bits = current_packet.m_type_id = input[index++] == '0' ? 15 : 11;
        int len = std::stoi(input.substr(index, len_bits), 0, 2);
        index += len_bits;

        int cur = 0;
        
        while (cur < len) {
            int pointer = index;
            Packet p = parse_packet(input, index);
            current_packet.sub_packets.push_back(p);
            cur += len_bits == 11 ? 1 : index - pointer;
        }
    }
    return current_packet;
}

int sum_version(Packet& p) {
    if (p.sub_packets.empty()) {
        return p.m_version;
    }
    int total = p.m_version;
    for (auto& sub : p.sub_packets) {
        total += sum_version(sub);
    }
    return total;
}

long long get_value(Packet& p) {
    long long to_return;
    switch(p.m_type) {
        case 0: {
            to_return = 0;
            for (auto& sub : p.sub_packets) {
                to_return += get_value(sub);
            }
            break;
        }
        case 1: {
            to_return = 1;
            for (auto& sub : p.sub_packets) {
                to_return *= get_value(sub);
            }
            break;
        }
        case 2: {
            to_return = std::numeric_limits<long long>::max();
            for (auto& sub : p.sub_packets) {
                auto val = get_value(sub);
                to_return = std::min(val, to_return);
            }
            break;
        }
        case 3: {
            to_return = std::numeric_limits<long long>::min();
            for (auto& sub : p.sub_packets) {
                auto val = get_value(sub);
                to_return = std::max(val, to_return);
            }
            break;
        }
        case 4: {
            to_return = p.m_value;
            break;
        }
        case 5: {
            to_return = get_value(p.sub_packets[0]) > get_value(p.sub_packets[1]) ? 1 : 0;
            break;
        }
        case 6: {
            to_return = get_value(p.sub_packets[0]) < get_value(p.sub_packets[1]) ? 1 : 0;
            break;
        }
        case 7: {
            to_return = get_value(p.sub_packets[0]) == get_value(p.sub_packets[1]) ? 1 : 0;
            break;
        }
    }
    return to_return;
}

int main(int argc, char *argv[]) {
    // Read input
    std::ifstream file;
#ifdef DEBUG
    file.open("test.txt");
#else
    file.open("input.txt");
#endif
	if (!file) {
        std::cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    std::vector<std::string> input {};
    std::cout << "Loading file...\n";
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        input.push_back(hex_str_to_bin_str(s));
    }
    file.close();
    Packet p;
    for (auto& line : input) {
        int start = 0;
        p = parse_packet(line, start);
        std::cout << "First exercise: " << sum_version(p) << std::endl;
        std::cout << "Second exercise: " << get_value(p) << std::endl;
    }

#ifdef DEBUG
    for (auto& line : input) {
        for (auto& c : line) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
#endif

    return 0;
}