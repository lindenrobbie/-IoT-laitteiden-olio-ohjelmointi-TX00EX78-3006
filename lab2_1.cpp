//
// Created by linde on 29/08/2026.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::string> find_all_elements (const std::string &xml, std::string tag_name)
{
    std::string start_of_tag = "<" + tag_name + ">";
    std::string end_of_tag = "</" + tag_name + ">";
    std::vector<std::string> elements;
    std::size_t search_position = 0;

    while (true)
    {
        std::size_t tag_start = xml.find(start_of_tag, search_position);

        if (tag_start == std::string::npos)
        {
            break;
        }

        std::size_t value_start = tag_start + start_of_tag.length();
        std::size_t tag_end = xml.find(end_of_tag, value_start);

        if (tag_end == std::string::npos)
        {
            break;
        }

        std::string value = xml.substr(value_start, tag_end - value_start);
        elements.push_back(value);
        search_position = tag_end + end_of_tag.length();
    }

    return elements;
}

int main(void)
{

    std::string xml_file_name;
    std::string xml_tag_name;
    std::string xml;
    std::string line;

    std::cout << "Input file name to open: " << std::endl;
    std::cin >> xml_file_name;

    std::ifstream xml_file(xml_file_name);

    while (std::getline(xml_file, line))
    {
        xml += line;
        xml += '\n';
    }


    while (true)
    {

        std::cout << "Input tag to find from '" << xml_file_name << "' or type 'stop' to stop: " << std::endl;
        std::cin >> xml_tag_name;

        if (xml_tag_name == "stop")
        {
            break;
        }

        std::vector<std::string> elements = find_all_elements(xml, xml_tag_name);

        if (elements.empty())
        {
            std::cout << "not found" << std::endl;
        }
        else
        {
            for (const std::string &element : elements)
            {
                std::cout << xml_tag_name << ": " << element << std::endl << std::endl;
            }
        }

    }

    return 0;

}

// file streams, inputs and outputs ifstream, ofstream

//// opened the file as a character stream,
//// copied its characters into a stringstream using the overloaded <<,
//// then used .str() to get one massive std::string

// changed this^^^^ absolutely horrible method
// now just using while loop and getline + \ni
