#include <iostream>
#include <fstream>
#include <time.h>

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

int main() {
    clock_t time = clock();
    std::ifstream file("./input.txt");

    int points_1 = 0;
    int points_2 = 0;

    for( std::string line; getline( file, line ); )
    {
        int a_int = int(line.at(0)) - 'A', 
            x_int = int(line.at(2)) - 'X';

        // Part 1
        points_1 += x_int + 1;
        int win_detection =  x_int - a_int;

        if(win_detection == 0) {
            points_1 += 3;
        } else if (win_detection == 1 || win_detection == -2) {
            points_1 += 6;
        }

        // Part 2
        points_2 += modulo(a_int + x_int - 1, 3) + 1;
        points_2 += x_int * 3;
    }

    std::cout << "Star One: " << points_1 << std::endl;
    std::cout << "Star Two: " << points_2 << std::endl;
    std::cout << (float) time / CLOCKS_PER_SEC << " Sekunden" << std::endl;

    return 0;
}
