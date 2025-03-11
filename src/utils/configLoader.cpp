#include "configLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>


ConfigLoader::ConfigLoader(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
		throw std::runtime_error("Impossible d'ouvrir le fichier de configuration !");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;  // Ignorer lignes vides et commentaires
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                data[key] = value;
            }
        }
    }
}

std::string ConfigLoader::getString(const std::string& key, const std::string& defaultValue) {
    return data.count(key) ? data[key] : defaultValue;
}

int ConfigLoader::getInt(const std::string& key, int defaultValue) {
    return data.count(key) ? std::stoi(data[key]) : defaultValue;
}

bool ConfigLoader::getBool(const std::string& key, bool defaultValue) {
    return data.count(key) ? (data[key] == "true") : defaultValue;
}