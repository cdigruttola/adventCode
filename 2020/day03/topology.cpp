#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int count_trees_for_slope(const std::vector<std::string>& tree_lines, int right, int down) {
    int index = right, tree_count = 0, line_length = tree_lines[0].length()-1;

    for (int i = down; i < tree_lines.size(); i += down) {
        
        if (tree_lines[i][index] == '#') {
            tree_count++;
        }

        index = (index + right) % line_length;
     }

    return tree_count;
}

int main() {
    // Read input

    std::ifstream file("topology.txt");
    std::vector<std::string> tree_lines{};
    
    for (std::string v; std::getline(file, v);) {
        tree_lines.push_back(v);
    }

    // Count trees with the given rules
    unsigned int r1d1 = count_trees_for_slope(tree_lines, 1, 1);
    unsigned int r3d1 = count_trees_for_slope(tree_lines, 3, 1); // This output is the solution for part 1
    unsigned int r5d1 = count_trees_for_slope(tree_lines, 5, 1);
    unsigned int r7d1 = count_trees_for_slope(tree_lines, 7, 1);
    unsigned int r1d2 = count_trees_for_slope(tree_lines, 1, 2);

    std::cout << "R1D1: " << r1d1 << std::endl;
    std::cout << "R3D1: " << r3d1 << std::endl;
    std::cout << "R5D1: " << r5d1 << std::endl;
    std::cout << "R7D1: " << r7d1 << std::endl;
    std::cout << "R1D2: " << r1d2 << std::endl;

    // Multiplication must be done on uint because the number is too high
    unsigned int result = r1d1 * r3d1 * r5d1 * r7d1 * r1d2;

    std::cout << "Part one solution: " << r3d1 << std::endl;
    std::cout << "Part two solution: " << result << std::endl;

    file.close();
}