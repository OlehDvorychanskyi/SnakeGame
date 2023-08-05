#pragma once
#include <map>
#include <string>
#include <sstream>

class ConfigLoader
{
private:
    std::map<std::string, std::map<std::string, std::string>> m_data;
public:
    bool load(const std::string& path);

    template <typename T>
    T get(const std::string& section, const std::string& key, const T& defaultValue);
};

template <typename T>
T ConfigLoader::get(const std::string& section, const std::string& key, const T& defaultValue)
{
    auto sectionIter = m_data.find(section);
    if (sectionIter != m_data.end()) 
    {
        auto keyIter = sectionIter->second.find(key);
        if (keyIter != sectionIter->second.end()) 
        {
            std::istringstream ss(keyIter->second);
            T value;
            if (ss >> value) 
                return value;
        }
    }
    return defaultValue;
}