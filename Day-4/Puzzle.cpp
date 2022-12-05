#include <iostream>
#include <fstream>

int main() {
    std::string line;
    std::ifstream file("input.txt");
    int count_1 = 0, count_2 = 0;

    while (getline(file, line))
    {
        std::string first_half = line.substr(0, line.find(','));
        std::string second_half = line.substr(line.find(',') + 1, line.length());

        int first_number = std::stoi(first_half.substr(0, first_half.find('-')));
        int second_number = std::stoi(first_half.substr(first_half.find('-') + 1, first_half.length()));
        int third_number = std::stoi(second_half.substr(0, second_half.find('-')));
        int fourth_number = std::stoi(second_half.substr(second_half.find('-') + 1, second_half.length()));

        std::cout << line << "    " << first_half << " : " << second_half << std::endl;

        if((first_number <= third_number && second_number >= fourth_number) || (first_number >= third_number && second_number <= fourth_number)) {
            count_1++;
        }

        if((second_number >= third_number && first_number <= fourth_number)  || (first_number >= fourth_number && second_number <= third_number)) {
            count_2++;
        }
    }

    std::cout << count_1 << std::endl;
    std::cout << count_2 << std::endl;

    return 0;
}