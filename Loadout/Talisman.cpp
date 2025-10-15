#include "Talisman.h"

// Constructor
Talisman::Talisman(const std::string& tName) {
    name = tName;
}

// Getter
std::string Talisman::getName() const {
    return name;
}

// Setter
void Talisman::setName(const std::string& newName) {
    name = newName;
}

// Print info
void Talisman::print() const {
    std::cout << "Talisman: " << name << std::endl;
}
