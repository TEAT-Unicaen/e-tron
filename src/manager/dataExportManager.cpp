#include <iostream>
#include "dataExportManager.h"

DataExportManager::DataExportManager(std::string name) noexcept : name(name) {}

DataExportManager::~DataExportManager() {}

void DataExportManager::addData(const std::string& key, const int value) {
	data[key] = value;
}