#include "ArmorSet.h"
#include <iostream>

// Add armor to the collection
void ArmorSet::addArmor(const Armor& armor) {
    armorList.push_back(armor);
}

// Print all armor pieces
void ArmorSet::printAll() const {
    std::cout << "Armor in Loadout:\n";
    for (const auto& a : armorList) {
        a.print();
    }
}

// Get number of armor pieces
size_t ArmorSet::size() const {
    return armorList.size();
}

// Get armor by index
Armor ArmorSet::getArmor(size_t index) const {
    if (index < armorList.size()) {
        return armorList[index];
    } else {
        // Return a default Armor if index is out of range
        return Armor("Unknown", "Unknown");
    }
}

void ArmorSet::clear() { 
    armorList.clear(); 
} 
