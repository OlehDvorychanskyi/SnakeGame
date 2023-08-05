#include "ConfigLoader.h"
#include <iostream>
#include <fstream>

bool ConfigLoader::load(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    std::string currentSection;
    
    while (std::getline(file, line))
    {
        if (line.empty() == false)
        {
            if (line[0] == '[' && line.back() == ']') 
            {
                currentSection = line.substr(1, line.size() - 2);
            }
            else 
            {
                size_t delimiterPos = line.find('=');
                if (delimiterPos != std::string::npos) 
                {
                    std::string key = line.substr(0, delimiterPos);
                    std::string value = line.substr(delimiterPos + 1);
                    m_data[currentSection][key] = value;
                }
            }
        }
    }
    return true;
}