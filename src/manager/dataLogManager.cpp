#include "DataLogManager.h"
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


void DataLogManager::addLog(const std::string& key, int value) {
    if (logDataDefault.find(key) != logDataDefault.end()) {
        logDataDefault[key] += value;
    }
    else {
        logDataDefault[key] = value;
    }
}

void DataLogManager::addMovement(const std::string& key, const std::string& dir, int value) {
    
    if (logDataMovement.find(key) == logDataMovement.end()) {
        logDataMovement[key] = {}; 
    }

    logDataMovement[key][dir] += value;  
}

void DataLogManager::addTick(const int& key, const std::string& log) {
	timeLog[key] = log;
}


int DataLogManager::getLog(const std::string& key) const {
    if (logDataDefault.find(key) != logDataDefault.end()) {
        return logDataDefault.at(key);
    }
    else {
        return 0;  
    }
}

void DataLogManager::fillJson(JsonWriter& writer) const {
	for (const auto& entry : logDataDefault) {
		writer.addJson(entry.first, entry.second);
	}
    for (const auto& entry : logDataMovement) {
        json playerMovement;

        for (const auto& directionEntry : entry.second) {
            playerMovement[directionEntry.first] = directionEntry.second;
        }

        writer.addJson(entry.first, playerMovement);
    }

    json tl;
    for (const auto& entry : timeLog) {
        tl[entry.first] = entry.second;
	}
	writer.addJson("timeLog", tl);
}