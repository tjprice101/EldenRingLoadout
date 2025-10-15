#include "Talismans.h"
#include <iostream>

// Add a new talisman to the collection
void Talismans::addTalisman(const Talisman& talisman) {
    talismanList.push_back(talisman);
}

// Print all talismans
void Talismans::printAll() const {
    std::cout << "Talismans in Loadout:\n";
    for (const auto& t : talismanList) {
        t.print();
    }
}

// Get number of talismans
size_t Talismans::size() const {
    return talismanList.size();
}

// Get talisman by index
Talisman Talismans::getTalisman(size_t index) const {
    if (index < talismanList.size()) {
        return talismanList[index];
    } else {
        // Return a default Talisman if index is out of range
        return Talisman("Unknown Talisman");
    }
}

void Talismans::clear() { 
    talismanList.clear(); 
} 