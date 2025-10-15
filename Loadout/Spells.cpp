#include "Spells.h"
#include <iostream>

// Add spell to the collection
void Spells::addSpell(const Spell& spell) {
    spellList.push_back(spell);
}

// Print all spells
void Spells::printAll() const {
    std::cout << "Spells in Loadout:\n";
    for (const auto& a : spellList) {
        a.print();
    }
}

// Get number of spells
size_t Spells::size() const {
    return spellList.size();
}

// Get spell by index
Spell Spells::getSpell(size_t index) const {
    if (index < spellList.size()) {
        return spellList[index];
    } else {
        // Return a default Spell if index is out of range
        return Spell("Unknown");
    }
}

void Spells::clear() { 
    spellList.clear(); 
} 
