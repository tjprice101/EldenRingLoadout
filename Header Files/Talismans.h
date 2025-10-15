#ifndef TALISMANS_H
#define TALISMANS_H

#include "Talisman.h"
#include <vector>

class Talismans {
private:
    std::vector<Talisman> talismanList;

public:
    // Add a new talisman
    void addTalisman(const Talisman& talisman);

    // Print all talismans
    void printAll() const;

    // Optional: get number of talismans
    size_t size() const;

    // Get talisman by index
    Talisman getTalisman(size_t index) const;

    
    void clear();
};

#endif
