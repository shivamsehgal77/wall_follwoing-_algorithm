#include <iostream>
#include <vector>

int main() {
    std::vector<std::pair<int, int>> path = {{1, 2}, {3, 4}, {5, 3}, {4, 5}, {6, 2}, {4, 5}, {6, 7}, {8, 8}, {2, 2}, {4, 5}, {5, 6}, {7, 8}};

    for (auto i = 3; i < path.size(); i++) {
        for (auto j = i + 1; j < path.size(); j++) {
            if (path.at(i).first == path.at(j).first && path.at(i).second == path.at(j).second) {
                path.erase(path.begin() + i + 1, path.begin() + j + 1);
                j=i;
            }
        }
    }

    std::cout << path.size() << "\n";
    for (int i = 0; i < 6; i++) {
        std::cout << path.at(i).first << path.at(i).second << '\n';
    }
}