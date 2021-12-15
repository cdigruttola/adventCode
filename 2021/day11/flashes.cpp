#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <numeric>
#include <regex>
#include <thread>

void print_steps(std::vector<std::vector<int>>& input, int step) {
#ifdef DEBUG
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::system("clear");
    std::cout << "Step " << step << std::endl;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 0) {
                std::cout << "\033[1;32m" << input[i][j] << "\033[0m";
            } else {
                std::cout << input[i][j];
            }
        }
        std::cout << std::endl;
    }
#endif
}

void flash(int i, int j, std::vector<std::vector<int>>& input, long& nr_flashes) {
    if (i < 0 || j < 0 || i >= input.size() || j >= input[0].size()) {
        return;
    }
    if (input[i][j] == 0 || ++input[i][j] <= 9) {
        return;
    }
    nr_flashes++;
    input[i][j] = 0;
    flash(i - 1, j, input, nr_flashes);
    flash(i + 1, j, input, nr_flashes);
    flash(i, j - 1, input, nr_flashes);
    flash(i, j + 1, input, nr_flashes);
    flash(i - 1, j - 1, input, nr_flashes);
    flash(i - 1, j + 1, input, nr_flashes);
    flash(i + 1, j - 1, input, nr_flashes);
    flash(i + 1, j + 1, input, nr_flashes);
}

bool check_synchronised(std::vector<std::vector<int>>& input) {
    int sum = std::accumulate(input.begin(), input.end(), 0, [](int init, const std::vector<int>& intvec) { 
            return std::accumulate(intvec.begin(), intvec.end(), init);
        }
    );
    return sum == 0;
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

    std::vector<std::vector<int>> input {};
    for (std::string s; std::getline(file, s);) {
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        std::vector<int> v {};
        for (auto& c : s) {
            v.push_back(c - '0');
        }
        input.push_back(v);
    }
    file.close();

    print_steps(input, 0);
    long nr_flashes = 0; 
    bool synchronised = false;
    int k = 0;
    while (!synchronised) {
        k++;
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                input[i][j]++;
            }
        }
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input[i].size(); j++) {
                if (input[i][j] > 9) {
                    flash(i, j, input, nr_flashes);
                }
            }
        }
        print_steps(input, k + 1);
        if (k == 100) {
            std::cout << "First exercise: " << nr_flashes << std::endl;
        }
        synchronised = check_synchronised(input);
    }

    std::cout << "Second exercise: " << k << std::endl;

    return 0;
}
