#include "Loadout.h"
#include <iostream>

// Constructor
Loadout::Loadout(const Stats& s, const Physic& p)
    : stats(s), physic(p) 
{
    for (int i = 0; i < 3; ++i) 
    {
        rightHanded[i] = nullptr;
        leftHanded[i] = nullptr;
    }
}

// Setters for weapons
void Loadout::setRightHandWeapon(int slot, Weapon* weapon) 
{
    if (slot >= 0 && slot < 3) 
    {
        rightHanded[slot] = weapon;
    } 
    else 
    {
        std::cerr << "Error: Right hand slot " << slot << " is out of range.\n";
    }
}

void Loadout::setLeftHandWeapon(int slot, Weapon* weapon) 
{
    if (slot >= 0 && slot < 3) 
    {
        leftHanded[slot] = weapon;
    } 
    else 
    {
        std::cerr << "Error: Left hand slot " << slot << " is out of range.\n";
    }
}

// Getters for weapons
Weapon* Loadout::getRightHandWeapon(int slot) const 
{
    if (slot >= 0 && slot < 3) 
    {
        return rightHanded[slot];
    } 
    else 
    {
        std::cerr << "Error: Right hand slot " << slot << " is out of range.\n";
        return nullptr;
    }
}

Weapon* Loadout::getLeftHandWeapon(int slot) const 
{
    if (slot >= 0 && slot < 3) 
    {
        return leftHanded[slot];
    } 
    else 
    {
        std::cerr << "Error: Left hand slot " << slot << " is out of range.\n";
        return nullptr;
    }
}

// Non-const getters
ArmorSet& Loadout::getArmorSet() 
{
    return armorSet;
}

Talismans& Loadout::getTalismans() 
{
    return talismans;
}

Spells& Loadout::getSpells() 
{
    return spells;
}

Physic& Loadout::getPhysic() 
{
    return physic;
}

Stats& Loadout::getStats() 
{
    return stats;
}

// Const getters
const ArmorSet& Loadout::getArmorSet() const 
{
    return armorSet;
}

const Talismans& Loadout::getTalismans() const 
{
    return talismans;
}

const Spells& Loadout::getSpells() const 
{
    return spells;
}

const Physic& Loadout::getPhysic() const 
{
    return physic;
}

const Stats& Loadout::getStats() const 
{
    return stats;
}

// Print full loadout
void Loadout::print() const 
{
    std::cout << "=== Loadout ===\n";

    std::cout << "Right Handed Weapons:\n";
    for (int i = 0; i < 3; ++i) 
    {
        if (rightHanded[i] != nullptr) 
        {
            std::cout << "Slot " << i + 1 << ": ";
            rightHanded[i]->print();
        } 
        else 
        {
            std::cout << "Slot " << i + 1 << ": EMPTY\n";
        }
    }

    std::cout << "Left Handed Weapons:\n";
    for (int i = 0; i < 3; ++i) 
    {
        if (leftHanded[i] != nullptr) 
        {
            std::cout << "Slot " << i + 1 << ": ";
            leftHanded[i]->print();
        } 
        else 
        {
            std::cout << "Slot " << i + 1 << ": EMPTY\n";
        }
    }

    std::cout << "\nArmor Set:\n";
    armorSet.printAll();

    std::cout << "\nTalismans:\n";
    talismans.printAll();

    std::cout << "\nSpells:\n";
    spells.printAll();

    std::cout << "\nPhysic:\n";
    physic.print();

    std::cout << "\nStats:\n";
    stats.print();
}
