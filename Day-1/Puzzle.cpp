#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

bool compare (int i,int j) { return (i>j); }

int main() {
    clock_t time = clock();
    std::ifstream file("input.txt");

    int current = 0;
    std::vector<int> list = { };

    for( std::string line; getline( file, line ); )
    {
        if(line == "") {
            list.push_back(current);
            current = 0;
            continue;
        }

        current += std::stoi(line);
    }

    std::sort(list.begin(), list.end(), compare);

    std::cout << "Star One: " << list.at(0) << std::endl;
    std::cout << "Star Two: " << (list.at(0) + list.at(1) + list.at(2)) << std::endl;
    std::cout << (float) time / CLOCKS_PER_SEC << " Sekunden" << std::endl;

    return 0;
}

