#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

std::ifstream input("input.txt");
std::string line;
std::vector<std::vector<int>> forest;
int tree_count = 0;
int highest_score = 0;

bool is_visible_from_outside(int x, int y) {
    int current = forest.at(y).at(x);

    // Temporary Vector from top to bottom at x
    std::vector<int> temp;

    for (int i = 0; i < forest.size(); i++)
    {
        temp.push_back(forest.at(i).at(x));
    }
    
    // Get Max at Top, Bottom, Left and Right from Tree we are watching
    int max_top = *std::max_element(temp.begin(), temp.begin() + y);
    int max_bottom = *std::max_element(temp.begin() + y + 1, temp.end());
    int max_left = *std::max_element(forest.at(y).begin(), forest.at(y).begin() + x);
    int max_right = *std::max_element(forest.at(y).begin() + x + 1, forest.at(y).end());

    // Tree is visible
    if(current > max_top || current > max_bottom || current > max_left || current > max_right) {
        return true;
    }

    // Tree is not visible
    return false;
}

int find_visible_trees(int x, int y) {
    int left = 0, right = 0, top = 0, bottom = 0;

    // Count visible trees going right from current tree
    for (int i = x + 1; i < forest.at(y).size(); i++)
    {
        right++;
        if(forest.at(y).at(i) >= forest.at(y).at(x)) {
            break;
        }
    }

    // Count visible trees going left from current tree
    for (int i = x - 1; i >= 0; i--)
    {
        left++;
        if (forest.at(y).at(i) >= forest.at(y).at(x))
        {
            break;
        }
    }

    // Temporary Vector from top to bottom at x
    std::vector<int> temp;

    for (int i = 0; i < forest.size(); i++)
    {
        temp.push_back(forest.at(i).at(x));
    }

    // Count visible trees going bottom from current tree
    for (int i = y + 1; i < forest.size(); i++)
    {
        bottom++;
        if (forest.at(i).at(x) >= forest.at(y).at(x))
        {   
            break;
        }
    }

    // Count visible trees going top from current tree
    for (int i = y - 1; i >= 0; i--)
    {
        top++;
        if (forest.at(i).at(x) == forest.at(y).at(x))
        {
            break;
        }
    }
    
    return left * right * top * bottom;
}

int main() {
    // Add all Numbers into 2-Dimensional Vector
    while (getline(input, line))
    {
        std::vector<int> row = {};

        for (int i = 0; i < line.length(); i++)
        {
            row.push_back(line.at(i) - '0');
        }
        
        forest.push_back(row);
    }

    // Add outside to Visible Trees
    tree_count += 2*(forest.size() + forest.at(0).size()) - 4;

    //Iterate over all Trees in the Center Square
    for (int i = 1; i < forest.size() - 1; i++)
    {
        for (int j = 1; j < forest.at(i).size() - 1; j++)
        {
            // Part 1
            if(is_visible_from_outside(j, i)) {
                tree_count++;
            }

            // Part 2
            int visible_tree_score = find_visible_trees(j, i);
            visible_tree_score > highest_score ? highest_score = visible_tree_score : true;
        }
    }
        
    std::cout << "Star One: " << tree_count << std::endl;
    std::cout << "Star Two: " << highest_score << std::endl;

    return 0;
}