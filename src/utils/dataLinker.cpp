#include "dataLinker.h"

DataLinker::DataLinker() {}

std::vector<DataLinker::Data>& DataLinker::getData() {
	return this->data;
}

std::pair<int, int> DataLinker::getInitPos(int id) {
	while (this->data.size() < id+1) {
		SLEEP_MS(5);
	}
	Data firstMove = this->data.at(id);
	
	return { firstMove.x, firstMove.y };
}

void DataLinker::addData(int id, int x, int y, int newX, int newY) {
	this->data.push_back({id, x, y, newX, newY});
}
