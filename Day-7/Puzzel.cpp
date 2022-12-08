#include <iostream>
#include <map>
#include <fstream>
#include <string>

int score_1 = 0;
int score_2 = 70000000;
int free_min = 0;

struct Directory
{
    int size;
    std::map<std::string, Directory*> subdirectorys;
    Directory* parent;
};

void go_through_directories(Directory* ptr) {
    // Go through every directory 
    // Add size to score if smaller equals to 100.000 (Part 1)
    if(ptr->size <= 100000) {
        score_1 += ptr->size;
    }

    // Find smallest dir to delete (Part 2)
    if(ptr->size >= free_min && ptr->size < score_2) {
        score_2 = ptr->size;
    }

    // Recursive call on all child directorys
    for (const auto& [dir_name, dir] : ptr->subdirectorys) {
        go_through_directories(dir);
    }
}

int main() {
    std::ifstream input("input.txt");
    std::string line;

    // Create root Directory and duplicate Pointer to run through Data structure
    Directory* root = new Directory;
    root->size = 0;
    root->parent = nullptr;
    root->subdirectorys = {};

    Directory* ptr = root;
    getline(input, line);

    // Parse Input to Tree like Structure
    while (getline(input, line))
    {
        // Irrelevant
        if(line == "$ ls") {
            continue;
        }

        // Create new subdirectory
        if(line.substr(0, 3) == "dir") {
            Directory* dir = new Directory;
            dir->size = 0;
            dir->parent = ptr;
            dir->subdirectorys = {};

            std::string dir_name = line.substr(4, line.length() - 4);
            
            ptr->subdirectorys[dir_name] = dir;
            continue;
        }

        // Switch directory
        if(line.substr(0, 4) == "$ cd") {
            // Directory Name
            std::string operation = line.substr(5, line.length() - 5);

            if(operation == "..") {
                // Go one Directory up
                ptr = ptr->parent;
            } else {
                // Go into Directory
                ptr = ptr->subdirectorys[operation];
    
            }
            continue;
        }

        // Update Current Dir Size
        std::string size_string = "";
        for (int i = 0; i < line.length(); i++)
        {
            if(line.at(i) == ' ') {
                break;
            }
            size_string += line.at(i);
        }
        ptr->size += std::stoi(size_string);

        // Increase size in higher directories 
        Directory* temp = ptr;
        while (temp->parent != nullptr)
        {
            temp = temp->parent;
            temp->size += std::stoi(size_string);
        }
    }

    // Part 1 and 2
    int free_space = 70000000 - root->size;
    free_min = 30000000 - free_space;
    go_through_directories(root);

    std::cout << "Star One: " << score_1 << std::endl;
    std::cout << "Star Two: " << score_2 << std::endl;

    return 0;
}