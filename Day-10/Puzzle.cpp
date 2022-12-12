#include <iostream>
#include <fstream>

int cycle = 0;
int register_X = 1;
int sum = 0;
int row_position = 0;

void check_register() {
    if(cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220) {
        sum += cycle * register_X;
    }
}

void draw_pixel() {
    char pixel = '.';
    
    if(row_position == register_X - 1 || row_position == register_X || row_position == register_X + 1 ) {
        pixel = '#';
    }

    row_position++;
    std::cout << pixel;

    if(row_position == 40) {
        row_position = 0;
        std::cout << std::endl;
    }
}

int main() {
    std::ifstream input("input.txt");
    std::string line;
    std::cout << "Star Two: " << std::endl;

    while (getline(input, line))
    {
        // Noop Operation
        if(line == "noop") {
            cycle++;
            draw_pixel();
            check_register();
            continue;
        }

        // AddX Operation
        int add = std::stoi(line.substr(5));
        for (int i = 0; i < 2; i++)
        {
            cycle++;
            draw_pixel();
            check_register();
        }
        register_X += add;
    }

    std::cout << std::endl;
    std::cout << "Star One: " << sum << std::endl;
    return 0;
}