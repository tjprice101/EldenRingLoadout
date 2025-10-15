#ifndef LOADOUT_SAVER_H
#define LOADOUT_SAVER_H

#include <string>
#include "Loadout.h"

class LoadoutSaver {
public:
    // Save the given loadout to a file with given name
    // Returns true if successful, false if a file with the same name already exists
    static bool saveLoadout(const Loadout& loadout, const std::string& fileName);
};

#endif
