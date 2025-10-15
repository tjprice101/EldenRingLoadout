#include "LoadoutSaver.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool LoadoutSaver::saveLoadout(const Loadout& loadout, const std::string& name) {
    std::string folder = "Saved Loadouts";
    if (!fs::exists(folder)) fs::create_directory(folder);

    std::string filePath = folder + "/" + name + ".txt";
    if (fs::exists(filePath)) {
        std::cout << "Error: A loadout with this name already exists.\n";
        return false;
    }

    std::ofstream outFile(filePath);
    if (!outFile.is_open()) { std::cout << "Error opening file.\n"; return false; }

    // --- Stats ---
    const Stats& s = loadout.getStats();
    outFile << s.getLevel() << " " << s.getVigor() << " " << s.getMind() << " "
            << s.getEndurance() << " " << s.getStrength() << " " << s.getDexterity() << " "
            << s.getIntelligence() << " " << s.getFaith() << " " << s.getArcane() << "\n";

    // --- Physic ---
    const Physic& p = loadout.getPhysic();
    outFile << p.getBubbleTear1() << "\n" << p.getBubbleTear2() << "\n";

    // --- Right Hand ---
    for (int i = 0; i < 3; ++i) {
        Weapon* w = loadout.getRightHandWeapon(i);
        if (w) outFile << w->getName() << " " << w->getAshOfWar() << " "
                       << w->getAffinity() << " " << w->getLevel() << "\n";
        else outFile << "EMPTY\n";
    }

    // --- Left Hand ---
    for (int i = 0; i < 3; ++i) {
        Weapon* w = loadout.getLeftHandWeapon(i);
        if (w) outFile << w->getName() << " " << w->getAshOfWar() << " "
                       << w->getAffinity() << " " << w->getLevel() << "\n";
        else outFile << "EMPTY\n";
    }

    // --- Armor ---
    const ArmorSet& armorSet = loadout.getArmorSet();
    size_t armorCount = armorSet.size();
    outFile << armorCount << "\n";
    for (size_t i = 0; i < armorCount; ++i) {
        Armor a = armorSet.getArmor(i);
        outFile << a.getTypeOfArmor() << " " << a.getName() << "\n";
    }

    // --- Talismans ---
    const Talismans& talismans = loadout.getTalismans();
    size_t talismanCount = talismans.size();
    outFile << talismanCount << "\n";
    for (size_t i = 0; i < talismanCount; ++i) {
        Talisman t = talismans.getTalisman(i);
        outFile << t.getName() << "\n";
    }

    // --- Spells ---
    const Spells& spells = loadout.getSpells();
    size_t spellCount = spells.size();
    outFile << spellCount << "\n";
    for (size_t i = 0; i < spellCount; ++i) {
        Spell sp = spells.getSpell(i);
        outFile << sp.getName() << "\n";
    }

    outFile.close();
    std::cout << "Loadout saved as \"" << name << "\"\n";
    return true;
}
