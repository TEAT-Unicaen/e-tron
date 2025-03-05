#include "JsonWriter.h"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

JsonWriter::JsonWriter(const std::string& filename) : filename(filename) {}

void JsonWriter::addJson(const std::string& key, const json& value) {
    jsonData[key] = value;
}

void JsonWriter::writeJson() {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return;
    }

    file << jsonData.dump(4);
    file.close();

    std::cout << "Fichier JSON écrit avec succès : " << filename << std::endl;
}

/* how to use : 

    JsonWriter writer("output.json");

    writer.addJson("name", "John Doe");
    writer.addJson("age", 30);
    writer.addJson("isStudent", false);
    writer.addJson("skills", json::array({"C++", "Python", "Lua"}));
    writer.addJson("address", {{"city", "Paris"}, {"country", "France"}});

    writer.writeJson();

*/