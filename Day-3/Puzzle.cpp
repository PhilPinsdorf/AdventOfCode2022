#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("./input.txt");
    std::string line;

    int points_1 = 0, points_2 = 0;

    while(getline( file, line ))
    {
        // Part 1 
        std::string first_half = line.substr(0, line.length() / 2);
        std::string second_half = line.substr(line.length() / 2, line.length() - 1);

        for(char& c : first_half) {
            if(second_half.find(c) != std::string::npos) {
                if(int(c) >= 'a') {
                    points_1 += c - 'a' + 1;
                } else {
                    points_1 += c - 'A' + 27;
                }
                break;
            }
        }
    }

    file.clear();
    file.seekg(0, std::ios::beg);

    while(getline( file, line ))
    {
        // Part 2
        std::string second; getline( file, second );
        std::string third; getline( file, third );

        for(char& c : line) {
            if(second.find(c) != std::string::npos &&
               third.find(c) != std::string::npos) {
                if(int(c) >= 'a') {
                    points_2 += int(c) - 'a' + 1;
                } else {
                    points_2 += int(c) - 'A' + 27;
                }
                break;
            }
        }
    }

    std::cout << "Star One: " << points_1 << std::endl;
    std::cout << "Star Two: " << points_2 << std::endl;

    return 0;
}