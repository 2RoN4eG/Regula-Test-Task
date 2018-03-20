#include "JsonWriter.h"

#include <fstream>
#include <iostream>

void WritePersonsToJsonFile (std::string fileName, std::vector <Person> persons)
{
    fileName += std::string ("_Result_") + std::string (".json");

    std::ofstream stream (fileName);

    if (persons.size () > 0)
    {
        /*std::cout*/stream << "{" << std::endl;
        /*std::cout*/stream << "\"Persons\": [" << std::endl;
    }

    for (size_t number = 0; number < persons.size (); ++ number)
    {
        Person person = persons [number];

        /*std::cout*/stream << "    {" << std::endl;
        /*std::cout*/stream << "        \"FilePath\": \""  << person.FileName  << "\"" << "," << std::endl;
        /*std::cout*/stream << "        \"Face\": {"   << std::endl;
        /*std::cout*/stream << "            \"X\": "    << person.Face.x            << "," << std::endl;
        /*std::cout*/stream << "            \"Y\": "    << person.Face.y            << "," << std::endl;
        /*std::cout*/stream << "            \"W\": "    << person.Face.width        << "," << std::endl;
        /*std::cout*/stream << "            \"H\": "    << person.Face.height       << "," << std::endl;
        /*std::cout*/stream << "        }"                                                 << std::endl;

        if (number + 1 < persons.size ())
        {
            /*std::cout*/stream << "    }" << "," << std::endl;
        }
        else
        {
            /*std::cout*/stream << "    }" << std::endl;
        }
    }

    if (persons.size () > 0)
    {
        /*std::cout*/stream << "    ]"    << std::endl;
        /*std::cout*/stream << "}"        << std::endl;
    }
}
