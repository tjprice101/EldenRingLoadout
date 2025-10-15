#ifndef ARMORSET_H
#define ARMORSET_H

#include "Armor.h"
#include <vector>

class ArmorSet {
private:
    std::vector<Armor> armorList;

public:
    // Add a new armor piece
    void addArmor(const Armor& armor);

    // Print all armor pieces
    void printAll() const;

    // Optional: get number of armor pieces
    size_t size() const;

    // Get armor by index
    Armor getArmor(size_t index) const;

    void clear();
};

#endif
