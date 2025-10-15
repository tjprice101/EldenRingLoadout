#include "LoadoutLoader.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

bool LoadoutLoader::loadLoadout(Loadout &loadout, const std::string &name)
{
    std::string folder = "Saved Loadouts";
    std::string filePath = folder + "/" + name + ".txt";

    if (!fs::exists(filePath))
    {
        std::cout << "Error: Loadout file does not exist.\n";
        return false;
    }

    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::cout << "Error: Could not open file for reading.\n";
        return false;
    }

    // --- Stats ---
    int level, vigor, mind, endurance, strength, dexterity, intelligence, faith, arcane;
    inFile >> level >> vigor >> mind >> endurance >> strength >> dexterity >> intelligence >> faith >> arcane;
    loadout.getStats() = Stats(level, vigor, mind, endurance, strength, dexterity, intelligence, faith, arcane);
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // --- Physic ---
    std::string bubble1, bubble2;
    std::getline(inFile, bubble1);
    std::getline(inFile, bubble2);
    loadout.getPhysic().setBubbleTear1(bubble1);
    loadout.getPhysic().setBubbleTear2(bubble2);

    // --- Right Hand Weapons ---
    for (int i = 0; i < 3; ++i)
    {
        std::string line;
        std::getline(inFile, line);
        if (line != "EMPTY")
        {
            std::istringstream iss(line);
            std::string n, ash, aff;
            int lvl;
            iss >> n >> ash >> aff >> lvl;
            loadout.setRightHandWeapon(i, new Weapon(n, ash, aff, lvl));
        }
        else
            loadout.setRightHandWeapon(i, nullptr);
    }

    // --- Left Hand Weapons ---
    for (int i = 0; i < 3; ++i)
    {
        std::string line;
        std::getline(inFile, line);
        if (line != "EMPTY")
        {
            std::istringstream iss(line);
            std::string n, ash, aff;
            int lvl;
            iss >> n >> ash >> aff >> lvl;
            loadout.setLeftHandWeapon(i, new Weapon(n, ash, aff, lvl));
        }
        else
            loadout.setLeftHandWeapon(i, nullptr);
    }

    // --- Armor ---
    size_t armorCount;
    inFile >> armorCount;
    inFile.ignore();
    for (size_t i = 0; i < armorCount; ++i)
    {
        std::string type, name;
        inFile >> type >> name;
        loadout.getArmorSet().addArmor(Armor(type, name));
    }

    // --- Talismans ---
    size_t talismanCount;
    inFile >> talismanCount;
    inFile.ignore();
    for (size_t i = 0; i < talismanCount; ++i)
    {
        std::string tname;
        std::getline(inFile, tname);
        loadout.getTalismans().addTalisman(Talisman(tname));
    }

    // --- Loading Spells ---
    size_t spellCount;
    inFile >> spellCount;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip line
    loadout.getSpells().clear();
    for (size_t i = 0; i < spellCount && i < 14; ++i)
    { // prevent overflow
        std::string spellName;
        std::getline(inFile, spellName);
        loadout.getSpells().addSpell(Spell(spellName));
    }

    inFile.close();
    std::cout << "Loadout \"" << name << "\" loaded successfully.\n";
    return true;
}
