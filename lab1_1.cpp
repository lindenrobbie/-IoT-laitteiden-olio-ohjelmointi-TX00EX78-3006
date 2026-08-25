//
// Created by linde on 22/08/2026.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int main ()
{

    int amount_of_numbers = {0};
    double sum = {0};

    std::cout << "Enter amount of numbers: " << std::endl;
    std::cin >> amount_of_numbers;
    std::vector<double> numbers(amount_of_numbers);

    for (int i = 0; i < amount_of_numbers; ++i)
    {
        double input = {0};
        std::cout << "Enter number " << i + 1 << ": " <<std::endl;
        std::cin >> input;
        numbers[i] = input;
    }

    for (int i = 0; i < numbers.size(); ++i)
    {
        sum += numbers[i];
        std::cout << std::fixed << std::setprecision(4) << "Number #" << i + 1 << ": " << numbers[i] << std::endl;
    }

    std::cout << std::fixed << std::setprecision(4) << "The sum of inputted numbers: " << sum << std::endl;

    return 0;
}


// dont forget to use correct data type, learn auto
// dont forget to use container in vector to determine type

// careful to init vector properly, initing size and using push back will append, not populate