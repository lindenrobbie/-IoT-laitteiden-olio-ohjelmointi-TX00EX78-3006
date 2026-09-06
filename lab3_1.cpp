//
// Created by linde on 06/09/2026.
//

// needs c++ 20
// g++ -std=c++20 lab3_1.cpp -o lab3_1
// ./lab3_1

// basically teaches some class stuff
// + how objects behave to operators
// 5 == 5 <-- c++ be like cool yea thats true
// e.g chicken == bread <-- c++ says wtf is this shit
// so we need to define it
// more examples are like std::cout << chicken;

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <compare>

// Implement class Item for storing grocery item information.
class Item
{
private: // All data members must be private.
    std::string name; // Name as std::string.
    int weight;       // Weight in grams as int.
    double price;     // Price in euros as double.
    int discount;     // Discount percentage as int.

public:
    // There must be a default constructor.
    Item()
    {
        name = "";
        weight = 1;
        price = 0.0;
        discount = 0;
    }

    // Constructor that takes the item information as parameters.
    Item(std::string item_name, int item_weight, double item_price, int item_discount)
    {
        name = item_name;
        weight = item_weight;
        price = item_price;
        discount = 0;
        setDiscount(item_discount);
    }

    // getDiscount: get the current discount percentage.
    int getDiscount() const
    {
        return discount;
    }

    // setDiscount: set the current discount percentage (0-100).
    void setDiscount(int new_discount)
    {
        if (new_discount >= 0 && new_discount <= 100)
        {
            discount = new_discount;
        }
    }

    // getPrice: get the price with the discount applied.
    double getPrice() const
    {
        double discount_amount = price * discount / 100.0;
        double final_price = price - discount_amount;
        return final_price;
    }

    // setPrice: set the price of the item.
    void setPrice(double new_price)
    {
        price = new_price;
    }

    // Three-way comparison by price/kg, with discount applied.
    std::partial_ordering operator<=>(const Item &other) const
    {
        double own_price_per_kg = getPrice() / (weight / 1000.0);
        double other_price_per_kg = other.getPrice() / (other.weight / 1000.0);
        return own_price_per_kg <=> other_price_per_kg;
    }

    // Equal-to comparison by price/kg, with discount applied.
    bool operator==(const Item &other) const
    {
        double own_price_per_kg = getPrice() / (weight / 1000.0);
        double other_price_per_kg = other.getPrice() / (other.weight / 1000.0);
        return own_price_per_kg == other_price_per_kg;
    }

    // These functions may access the private variables because they are friends.
    friend std::ostream &operator<<(std::ostream &output, const Item &item);
    friend std::istream &operator>>(std::istream &input, Item &item);
};

// Output operator: print the item in JSON format, without a newline.
std::ostream &operator<<(std::ostream &output, const Item &item)
{
    output << "{ \"Name\":\"" << item.name << "\"";
    output << ", \"Weight\":" << item.weight;
    output << ", \"Price\":" << item.price;
    output << ", \"Discount\":" << item.discount << " }";
    return output;
}

// Input operator: read the format produced by the output operator.
// "The input operator must set the fail-bit if parsing input fails."
std::istream &operator>>(std::istream &input, Item &item)
{
    // Read the four fields in the order shown in the lab.
    std::string fields[4] = {"\"Name\"", "\"Weight\"", "\"Price\"", "\"Discount\""};
    char separators[4] = {'{', ',', ',', ','};
    std::string field;
    char character = 0;

    for (int i = 0; i < 4; ++i)
    {
        input >> character;
        if (!input || character != separators[i])
        {
            input.setstate(std::ios::failbit);
            return input;
        }

        input >> std::ws; // Skip whitespace before the field name.
        std::getline(input, field, ':');
        // Parsing must fail if the JSON field names do not match.
        if (!input || field != fields[i])
        {
            input.setstate(std::ios::failbit);
            return input;
        }

        if (i == 0)
        {
            input >> character;
            if (!input || character != '"')
            {
                input.setstate(std::ios::failbit);
                return input;
            }
            std::getline(input, item.name, '"'); // The name may contain spaces.
        }
        else if (i == 1)
        {
            input >> item.weight;
        }
        else if (i == 2)
        {
            input >> item.price;
        }
        else
        {
            input >> item.discount;
        }
    }

    input >> character; // Input must not require a newline after the JSON.
    if (!input || character != '}')
    {
        input.setstate(std::ios::failbit);
    }
    return input;
}

void sortAndPrint(std::vector<Item> &items)
{
    // Sort the vector using std::sort.
    std::sort(items.begin(), items.end());
    double total = 0.0;

    for (std::size_t i = 0; i < items.size(); ++i)
    {
        // Each item on a separate line, with an index number.
        std::cout << i << ": " << items[i] << '\n';
        total += items[i].getPrice();
    }
    // Print the net worth of the stock after the list.
    std::cout << "Net worth of stock: " << total << " euros\n";
}

int main()
{
    std::vector<Item> items; // Define a vector of Items.
    std::string name;

    // Ask for the name, "stop" to finish, or "json" for JSON input.
    while (true)
    {
        std::cout << "Item name, 'json', or 'stop': ";
        std::getline(std::cin >> std::ws, name);
        if (name == "stop")
        {
            break;
        }

        Item item;
        if (name == "json")
        {
            std::cout << "Enter JSON: ";
            std::cin >> item;
        }
        else
        {
            int weight;
            double price;
            int discount;
            std::cout << "Weight in grams: ";
            std::cin >> weight;
            std::cout << "Price in euros: ";
            std::cin >> price;
            std::cout << "Discount percentage: ";
            std::cin >> discount;
            item = Item(name, weight, price, discount);
        }
        items.push_back(item); // Add each entered item to the vector.
    }

    sortAndPrint(items); // Sort and print after all items have been entered.

    // Ask for an item index to change, or "stop" to end the program.
    while (true)
    {
        std::string choice;
        std::cout << "Item index, or 'stop': ";
        std::cin >> choice;
        if (choice == "stop")
        {
            break;
        }

        int index = std::stoi(choice); // Convert the index text to an integer.
        int discount;
        // Ask for a discount percentage for the chosen item.
        std::cout << "New discount percentage: ";
        std::cin >> discount;
        items[index].setDiscount(discount);
        sortAndPrint(items); // Sort and print again, then ask for another item.
    }
    return 0;
}
