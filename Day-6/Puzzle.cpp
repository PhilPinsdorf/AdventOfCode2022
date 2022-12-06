#include <iostream>
#include <fstream>
#include <algorithm>

int find_different(int pos, int n, std::string text) {
    for (int i = 0; i < (n - 1); i++)
    {
        int from = pos - (n - 1) + i;
        std::string match = text.substr(from, (n - 1 - i));
        char find = text.at(pos - n + i);

        if(match.find(find) != std::string::npos) {
            return find_different(pos + 1, n, text);
        }
    }

    return pos;
}

int main() {
    std::ifstream input("input.txt");
    std::string line; getline(input, line); 

    int position_1 = find_different(4, 4, line);
    int position_2 = find_different(14, 14, line);

    std::cout << "Star One: " << position_1 << std::endl;
    std::cout << "Star Two: " << position_2 << std::endl;
    return 0;
}