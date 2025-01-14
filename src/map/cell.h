#pragma once

#include <string>

class Cell {

public:
    Cell();
    Cell(const std::string& name);
    ~Cell();

    std::string getName() const;

private:
    std::string name; 
};
