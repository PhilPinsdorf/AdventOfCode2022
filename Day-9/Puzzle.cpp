#include <iostream>
#include <set>
#include <fstream>
# include <vector>

struct Position
{
    int x, y;

    bool operator <(const Position& pt) const
    {
        return (x < pt.x) || ((!(pt.x < x)) && (y < pt.y));
    }
};


int main() {
    Position head = {0, 0};
    Position tail = {0, 0};
    std::vector<Position> rope_positions(10, {0, 0});
    std::set<Position> tail_positions_1;
    std::set<Position> tail_positions_2;

    std::string line;
    std::ifstream input("input.txt"); 

    while(getline(input, line)) {
        char direction = line.at(0);
        int iterations = std::stoi(line.substr(2));

        for (int i = 0; i < iterations; i++)
        {
            // Move Head
            switch (direction)
            {
                case 'U':
                    head.y += 1;
                    rope_positions.at(0).y += 1;
                    break;

                case 'D':
                    head.y -= 1;
                    rope_positions.at(0).y -= 1;
                    break;

                case 'L':
                    head.x -= 1;
                    rope_positions.at(0).x -= 1;
                    break;

                case 'R':
                    head.x += 1;
                    rope_positions.at(0).x += 1;
                    break;
                
                default:
                    break;
            }

            // Part One
            if (std::abs(head.x - tail.x) > 1)
            {
                tail.y = head.y;
                tail.x += (head.x - tail.x) / 2;
            } else if (std::abs(head.y - tail.y) > 1) {
                tail.x = head.x;
                tail.y += (head.y - tail.y) / 2;
            }

            tail_positions_1.insert(tail);

            // Part Two
            for (int j = 1; j < 10; j++)
            {
                if (std::abs(rope_positions.at(j - 1).x - rope_positions.at(j).x) > 1)
                {
                    rope_positions.at(j).y = rope_positions.at(j - 1).y;
                    rope_positions.at(j).x += (rope_positions.at(j - 1).x - rope_positions.at(j).x) / 2;
                } else if (std::abs(rope_positions.at(j - 1).y - rope_positions.at(j).y) > 1) {
                    rope_positions.at(j).x = rope_positions.at(j - 1).x;
                    rope_positions.at(j).y += (rope_positions.at(j - 1).y - rope_positions.at(j).y) / 2;
                }
            }

            tail_positions_2.insert(rope_positions.at(9));
        }
    }

    std::cout << "Star One: " << tail_positions_1.size() << std::endl;
    std::cout << "Star Two: " << tail_positions_2.size() << std::endl;

    return 0;
}