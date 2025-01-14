#include "cell.h"

Cell::Cell() : name("Unnamed") {}

Cell::Cell(const std::string& name) : name(name) {
}

Cell::~Cell() {
}

std::string Cell::getName() const {
    return name;
}
