#ifndef LOADOUT_H
#define LOADOUT_H

#include "Weapon.h"
#include "ArmorSet.h"
#include "Talismans.h"
#include "Physic.h"
#include "Stats.h"
#include "Spells.h"
#include "Spell.h"

class Loadout {
private:
    Weapon* rightHanded[3];
    Weapon* leftHanded[3];
    ArmorSet armorSet;
    Talismans talismans;
    Spells spells;
    Physic physic;
    Stats stats;

public:
    // Constructor
    Loadout(const Stats& s, const Physic& p);

    // Setters for Weapons
    void setRightHandWeapon(int slot, Weapon* weapon);
    void setLeftHandWeapon(int slot, Weapon* weapon);

    // Getters for Weapons
    Weapon* getRightHandWeapon(int slot) const;
    Weapon* getLeftHandWeapon(int slot) const;

    // Access armor, talismans, physic, stats, and spells
    ArmorSet& getArmorSet();
    Talismans& getTalismans();
    Spells& getSpells();
    Physic& getPhysic();
    Stats& getStats();

    const ArmorSet& getArmorSet() const;
    const Talismans& getTalismans() const;
    const Spells& getSpells() const;
    const Physic& getPhysic() const;
    const Stats& getStats() const;

    // Print full loadout
    void print() const;
};

#endif
