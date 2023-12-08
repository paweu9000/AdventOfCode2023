#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int get_nums(std::string text)
{
    std::vector<char> c_nums;
    for (int i = 0; i < text.size(); i++)
    {
        if (isdigit(text[i])) c_nums.push_back(text[i]);
    }
    if (c_nums.size() == 1) 
    {
        return stoi(std::string(1, c_nums[0])+c_nums[0]);
    }
    else 
    {
        return stoi(std::string(1, c_nums[0])+c_nums[c_nums.size()-1]);
    }
}

int main() 
{
    int sum = 0;
    std::string line;
    std::ifstream file("input.txt");
    if (file.is_open())
    {
        while (file.good())
        {
            std::getline(file, line);
            sum += get_nums(line);
        }
        file.close();
    }
    std::cout << sum << std::endl;
    return 0;
}