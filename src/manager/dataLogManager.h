#ifndef DATALOGMANAGER_H
#define DATALOGMANAGER_H

#include <string>
#include <unordered_map>

#include "../utils/jsonWriter.h"

class DataLogManager {
public:
    DataLogManager() = default;
    ~DataLogManager() = default;

    void addLog(const std::string& key, int value);
    void addMovement(const std::string& key, const std::string& dir, int value);

    int getLog(const std::string& key) const;

    void fillJson(JsonWriter& writer) const;

private:
    std::unordered_map<std::string, int> logDataDefault;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> logDataMovement;
};

#endif