//
// Created by linde on 30/08/2026.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>



class RunningAverage
{
private:
    std::deque<int> values;
    std::size_t maximum_values;

public:
    // construcc
    RunningAverage(std::size_t size)
    {
        maximum_values = size;
    }

    // methods
    void add_value(int value)
    {
        values.push_back(value);

        if (values.size() > maximum_values)
        {
            values.pop_front();
        }
    }

    double get_average()
    {
        if (values.empty())
        {
            return 0.0;
        }

        int sum = 0;

        for (int value: values)
        {
            sum += value;
        }

        double average = static_cast<double>(sum) / values.size();
        return average;
    }

};

int main()
{
    RunningAverage average(5);
    int input;

    while (true)
    {
        std::cout << "Enter a number or '0' to stop: " << std::endl;
        std::cin >> input;

        if (input == 0)
        {
            std::cout << "Current running average: " << average.get_average() << std::endl;
            break;
        }

        average.add_value(input);

        std::cout << "Current running average: " << average.get_average() << std::endl;

    }

    return 0;

}

// deque = an array of pointers to other arrays:
// pointer array [p0, p1, p2, p3]
//               [a0][b0][c0][d0]
//               [a1][b1][c1][d1]
//               [a2][b2][c2][d2]
//               etc etc etc etc

// idk if its a matrix or 2d array, or whatever people would call it
// dynamic array of pointers (vector?)
