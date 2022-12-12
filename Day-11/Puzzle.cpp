#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

struct Monkey
{
    std::queue<unsigned long long> items;
    std::string increase_worry_level;
    int div_test, monkey_true, monkey_false;
    unsigned long long inspected;
};

bool compare (unsigned long long i,unsigned long long j) { return (i>j); }

unsigned long long calculate(unsigned long long a, std::string c, unsigned long long b) {
    if (c == "+")
    {
        return a + b;
    }

    return a*b;
}

int main() {
    std::string line;
    std::ifstream input("input.txt");
    std::vector<Monkey> monkeys;
    int mod = 1;

    // Parse Monkeys
    while (getline(input, line))
    {
        Monkey monkey = Monkey();
        
        // Items
        getline(input, line);
        line = line.substr(18);
        line = std::regex_replace(line, std::regex(", "), ",");
        std::stringstream streamData(line);
        std::string val;

        while (getline(streamData, val, ',')) {
            monkey.items.push(std::stoi(val));
        }

        // Operation
        getline(input, line);
        monkey.increase_worry_level = line.substr(19);

        // Test
        getline(input, line);
        monkey.div_test = std::stoi(line.substr(21));

        // Monkey true
        getline(input, line);
        monkey.monkey_true = std::stoi(line.substr(29));

        // Monkey false
        getline(input, line);
        monkey.monkey_false = std::stoi(line.substr(30));

        // Inspected
        monkey.inspected = 0;

        // Skip Empty Line
        getline(input, line);

        monkeys.push_back(monkey);
    }

    // Find common denominator
    for (int i = 0; i < monkeys.size(); i++)
    {
        mod *= monkeys.at(i).div_test;
    }    

    // Part Two (You can imagine how part One looked)
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < monkeys.size(); j++)
        {
            while (!monkeys.at(j).items.empty())
            {
                // Update Inspection
                monkeys.at(j).inspected++;

                // Increase worry Level
                unsigned long long curr_item = monkeys.at(j).items.front();
                monkeys.at(j).items.pop();
                std::string curr_item_string = std::to_string(curr_item);
                std::string eval = std::regex_replace(monkeys.at(j).increase_worry_level, std::regex("old"), curr_item_string);

                std::vector<std::string> parts;
                std::stringstream streamData(eval);
                std::string val;

                while (getline(streamData, val, ' ')) {
                    parts.push_back(val);
                }

                curr_item = calculate(std::stoull(parts.at(0)), parts.at(1), std::stoull(parts.at(2)));

                // Keep at humane levels 
                curr_item %= mod;

                // Division Test
                if(curr_item % monkeys.at(j).div_test == 0) {
                    monkeys.at(monkeys.at(j).monkey_true).items.push(curr_item);
                } else {
                    monkeys.at(monkeys.at(j).monkey_false).items.push(curr_item);
                }
            }
        }
    }
    
    std::vector<unsigned long long> inspections;
    for (int i = 0; i < monkeys.size(); i++)
    {
        inspections.push_back(monkeys.at(i).inspected);
    }
    
    std::sort(inspections.begin(), inspections.end(), compare);
    std::cout << "Star Two: " << (inspections.at(0) * inspections.at(1)) << std::endl;
    
    return 0;
}