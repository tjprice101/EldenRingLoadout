#ifndef LOADOUT_LOADER_H
#define LOADOUT_LOADER_H

#include <string>
#include "Loadout.h"

class LoadoutLoader {
public:
    // Load a loadout from a file
    // Returns true if successful, false otherwise
    static bool loadLoadout(Loadout& loadout, const std::string& fileName);
};

#endif
