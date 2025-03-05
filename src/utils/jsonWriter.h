#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <string>
#include <nlohmann/json.hpp>

class JsonWriter {
public:
    JsonWriter(const std::string& filename);
    void addJson(const std::string& key, const nlohmann::json& value);
    void writeJson();

private:
    std::string filename;
    nlohmann::json jsonData;
};

#endif
