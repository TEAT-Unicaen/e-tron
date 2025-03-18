#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class ConfigLoader {
public:
    ConfigLoader(const std::string& filename);
    ~ConfigLoader() = default;

    std::string getString(const std::string& key, const std::string& defaultValue = "");
    int getInt(const std::string& key, int defaultValue = 0);
    bool getBool(const std::string& key, bool defaultValue = false);

private:
    std::unordered_map<std::string, std::string> data;
};
