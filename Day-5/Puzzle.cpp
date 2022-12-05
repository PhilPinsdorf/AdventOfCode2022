#include <iostream>
#include <stack>
#include <fstream>
#include <regex>

std::stack<char> container_1[9];
std::stack<char> container_2[9];
std::ifstream input("input.txt");
std::string line;
std::regex rgx("move ([0-9]+) from ([0-9]) to ([0-9])");
std::smatch match;

void reverseStack(std::stack<char>& stack)
{
   char item;
   std::stack<char> tmpStack;

   while (stack.empty() == false)
   {
      item = stack.top();
      stack.pop();
      tmpStack.push(item);
   }

   stack = tmpStack;
   return;
}

void parseInput() {
   while (getline(input, line))
   {
      if(line == " 1   2   3   4   5   6   7   8   9 ") {
         getline(input, line);
         break;
      }

      for (size_t i = 0; i < 9; i++)
      {
         char c = line.at(1 + (i * 4));
         if(c != ' ') {
            container_1[i].push(c);
            container_2[i].push(c);
         }
      }      
   }

   for (size_t i = 0; i < 9; i++)
   {
      reverseStack(container_1[i]);
      reverseStack(container_2[i]);
   }
}

int main() {
   parseInput();
   
   while (getline(input, line))
   {
      std::regex_match(line, match, rgx);

      int iterations = std::stoi(match[1].str());
      int from = std::stoi(match[2].str()) - 1;
      int to = std::stoi(match[3].str()) - 1;
      
      // Part 1
      for (int i = 0; i < iterations; i++)
      {
         char c = container_1[from].top();
         container_1[to].push(c);
         container_1[from].pop();
      }

      // Part 2
      std::stack<char> tempStack;

      for (int i = 0; i < iterations; i++)
      {
         char c = container_2[from].top();
         tempStack.push(c);
         container_2[from].pop();
      }

      for (int i = 0; i < iterations; i++)
      {
         container_2[to].push(tempStack.top());
         tempStack.pop();
      }
   }

   std::cout << "Star One: ";
   for (size_t i = 0; i < 9; i++) { std::cout << container_1[i].top(); }
   std::cout << std::endl;

   std::cout << "Star Two: ";
   for (size_t i = 0; i < 9; i++) { std::cout << container_2[i].top(); }
   std::cout << std::endl;

   return 0;
}