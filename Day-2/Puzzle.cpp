#include <iostream>
#include <fstream>

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

int main() {
    std::ifstream file("./input.txt");

    int points_1 = 0;
    int points_2 = 0;

    for( std::string line; getline( file, line ); )
    {
        // Part 1
        points_1 += (int(line.at(2)) - 'W');
        int win_detection =  (int(line.at(2)) - 'X') - (int(line.at(0)) - 'A');

        if(win_detection == 0) {
            points_1 += 3;
        } else if (win_detection == 1 || win_detection == -2) {
            points_1 += 6;
        }

        // Part 2
        points_2 += modulo(((int(line.at(0)) - 'A') + (int(line.at(2)) - 'Y')), 3) + 1;

        if(line.at(2) == 'Y') {
            points_2 += 3;
        } else if (line.at(2) == 'Z') {
            points_2 += 6;
        }
    }

    std::cout << "Star One: " << points_1 << std::endl;
    std::cout << "Star Two: " << points_2 << std::endl;

    return 0;
}
