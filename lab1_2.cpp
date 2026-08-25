//
// Created by linde on 25/08/2026.
//

#include <iostream>
#include <string>


bool swap(std::string &input, char target_char, char replace_char)
{
    std::string string_before = input;

    for (std::string::size_type i = 0; i < input.size(); ++i)
    {
        if (input[i] == target_char)
        {
            input[i] = replace_char;
        }

    }

    if (string_before == input)
    {
        return false;
    }

    return true;

}


int main()
{
    std::string input = "";
    char target_char;
    char replace_char;

    while (1)
    {
        std::cout << "Enter a string or 'stop' to stop: " << std::endl;
        std::getline(std::cin >> std::ws, input);

        if (input == "stop")
        {
            break;
        }

        std::cout << "Enter target character: " << std::endl;
        std::cin.get(target_char);
        std::cin.ignore();

        std::cout << "Enter replacement character: " << std::endl;
        std::cin.get(replace_char);
        std::cin.ignore();

        if (swap(input, target_char, replace_char) == true)
        {
            std::cout << input << std::endl << std::endl;
        }

    }

    return 0;

}

// input sanitizing is annoying in c++
// cin.get gets 1 char
// cin.ignore ignores whitespace as input


// pass by value does not mean by int lol
// i++ copies, ++i increments (++i = more efficient)
