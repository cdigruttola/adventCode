#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>

#define N 9


int64_t solve(int days, std::array<int64_t, N> lanternfishes) {
    for (int i = 0; i < days; i++) {
        auto next_lantern = lanternfishes[0];
        for (int j = 1; j < N; j++) {
            lanternfishes[j - 1] = lanternfishes[j];
        }
        lanternfishes[6] += next_lantern;
        lanternfishes[8] = next_lantern;
    }
    int64_t init = 0;
    return std::accumulate(lanternfishes.begin(), lanternfishes.end(), init);
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

    std::array<int64_t, N> lanternfishes {};
    for (std::string v; std::getline(file, v, ',');) {
        lanternfishes[stoi(v)]++;
    }

    file.close();

    std::cout << "First exercise: " << solve(80, lanternfishes) << std::endl;
    std::cout << "Second exercise: " << solve(256, lanternfishes) << std::endl;

    return 0;
}