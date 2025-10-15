#include "Armor.h"

// Constructor
Armor::Armor(const std::string& aType, const std::string& aName) {
    typeOfArmor = aType;
    name = aName;
}

// Getters
std::string Armor::getTypeOfArmor() const { 
    return typeOfArmor; 
}

std::string Armor::getName() const { 
    return name; 
}

// Setters
void Armor::setTypeOfArmor(const std::string& newType) { 
    typeOfArmor = newType; 
}
void Armor::setName(const std::string& newName) { 
    name = newName; 
}

// Print info
void Armor::print() const {
    std::cout << typeOfArmor << ": " << name << std::endl;
}
