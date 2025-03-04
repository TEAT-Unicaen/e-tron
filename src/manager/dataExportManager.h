#include <nlohmann/json.hpp>

class DataExportManager {

public:
    DataExportManager(std::string name) noexcept;
    ~DataExportManager();

    void addData(const std::string& key, const int value);

private:
    nlohmann::json data;
    std::string name;
};