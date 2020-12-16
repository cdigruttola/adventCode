#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>

void split(std::string s, std::string delimiter, std::vector<std::string>& tokens) {
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
}

std::pair<long, long> busId (long timestamp, std::vector<std::string>& buses) {
	for (long i = timestamp; ; ++i) {
    	for (std::string str : buses) {
    		if (str != "x") {
    			int busId = std::stoi(str);
    			if (i % busId == 0) {
    				return std::make_pair(busId, i - timestamp);
    			}
    		}
    	}
    }
    return std::make_pair(0 ,0);
}

long long bruteForceChallange(std::vector<std::string>& buses) {
    // l'offset è la posizione nel vettore
    bool found = false;
    long long timestamp = 0;
    while(!found) {
        bool foundInner = true;
        for (int i = 0; i < buses.size(); ++i) {
            if (buses[i] == "x") {
                continue;
            }
            long long busId = std::stoll(buses[i]);
            if ((timestamp + i) % busId != 0) {
                foundInner = false;
                break;
            }
        }
        if (foundInner) {
            found = true;
        } else {
            ++timestamp;
        }
    }
    return timestamp;
}

template<typename _Ty> _Ty mulInv(_Ty a, _Ty b) {
    _Ty b0 = b;
    _Ty x0 = 0;
    _Ty x1 = 1;
 
    if (b == 1) {
        return 1;
    }
 
    while (a > 1) {
        _Ty q = a / b;
        _Ty amb = a % b;
        a = b;
        b = amb;
 
        _Ty xqx = x1 - q * x0;
        x1 = x0;
        x0 = xqx;
    }
 
    if (x1 < 0) {
        x1 += b0;
    }
 
    return x1;
}
 
template<typename _Ty> _Ty chineseRemainderTheorem(std::vector<_Ty> n, std::vector<_Ty> a) {
    _Ty prod = 1;
    for (_Ty v : n) {
        prod *= v;
    }
    std::cout << prod << "\n";
    _Ty sm = 0;
    for (int i = 0; i < n.size(); i++) {
        _Ty p = prod / n[i];
        sm += a[i] * mulInv(p, n[i]) * p;
    }
 
    return sm % prod;
}


int main() {
    // Read input

    std::ifstream file;
#ifdef DEBUG
    file.open("debug.txt");
#else
    file.open("day13.txt");
#endif
	if (!file) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    long timestamp;
    std::string bus_lines;
    file >> timestamp;
    file >> bus_lines;

    file.close();

    std::vector<std::string> buses;
    split(bus_lines, ",", buses);
    auto resultPart1 = busId(timestamp, buses);
    std::cout << (resultPart1.first * resultPart1.second) << "\n";
    std::vector<unsigned long long int> n;
    std::vector<unsigned long long int> a;
    a.push_back(0);
    n.push_back(std::stoll(buses[0]));
    for (int i = 1; i < buses.size(); ++i) {
        if (buses[i] != "x") {
            n.push_back(std::stoll(buses[i]));
            a.push_back(std::stoll(buses[i]) - i);
        }
    }
    // std::cout << bruteForceChallange(buses) << "\n";
    std::cout << chineseRemainderTheorem(n, a) << "\n";
}