#ifndef SPELLS_H
#define SPELLS_H

#include "Spell.h"
#include <vector>

class Spells {
private:
    std::vector<Spell> spellList;

public:
    // Add a new armor piece
    void addSpell(const Spell& spell);

    // Print all spells
    void printAll() const;

    // Optional: get number of spells
    size_t size() const;

    // Get spell by index
    Spell getSpell(size_t index) const;

    void clear();
};

#endif
