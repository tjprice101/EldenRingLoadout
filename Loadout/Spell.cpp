#include "Spell.h"

// Constructor
Spell::Spell(const std::string& spellName) {
    name = spellName;
}

// Getters 
std::string Spell::getName() const { 
    return name; 
}

// Setters
void Spell::setName(const std::string& newName) { 
    name = newName; 
}

// Print info
void Spell::print() const {
    std::cout << name << std::endl;
}
