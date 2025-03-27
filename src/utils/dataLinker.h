#pragma once

#include <vector>
#include <utility>

#include "utils.h"

class DataLinker {
public:
    DataLinker();
    ~DataLinker() = default;

	struct Data {
		int id;
		int x;
		int y;
		int newX;
		int newY;
		bool isAlive = true;
	};
    //Methods 
	void addData(int id, int x, int y, int newX, int newY, bool isAlive);
    std::vector<DataLinker::Data>& getData();
	std::pair<int, int> DataLinker::getInitPos(int id);
private:
	//Attributes
	std::vector<DataLinker::Data> data;
};