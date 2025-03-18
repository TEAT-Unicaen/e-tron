#pragma once

#include <vector>
#include <utility>

class DataLinker {
public:
    DataLinker();
    ~DataLinker() = default;

    //Methods 
    void addData(int id, int x, int y, int newX, int newY);
    std::vector<std::pair<int, std::vector<int>>> requestData();

private:

	//Attributes
    std::vector<std::pair<int, std::vector<int>>> data;
};