#include "Stats.h"

// Constructor
Stats::Stats(int lvl, int vig, int min, int end, int str, int dex, int intl, int fai, int arc) {
    level = lvl;
    vigor = vig;
    mind = min;
    endurance = end;
    strength = str;
    dexterity = dex;
    intelligence = intl;
    faith = fai;
    arcane = arc;
}

// Getters
int Stats::getLevel() const { 
    return level; 
}
int Stats::getVigor() const { 
    return vigor; 
}
int Stats::getMind() const { 
    return mind; 
}
int Stats::getEndurance() const { 
    return endurance; 
}
int Stats::getStrength() const { 
    return strength; 
}
int Stats::getDexterity() const { 
    return dexterity; 
}
int Stats::getIntelligence() const { 
    return intelligence; 
}
int Stats::getFaith() const { 
    return faith; 
}
int Stats::getArcane() const { 
    return arcane; 
}

// Setters
void Stats::setLevel(int lvl) { 
    level = lvl; 
}
void Stats::setVigor(int vig) { 
    vigor = vig; 
}
void Stats::setMind(int min) { 
    mind = min; 
}
void Stats::setEndurance(int end) { 
    endurance = end; 
}
void Stats::setStrength(int str) { 
    strength = str; 
}
void Stats::setDexterity(int dex) { 
    dexterity = dex; 
}
void Stats::setIntelligence(int intl) { 
    intelligence = intl; 
}
void Stats::setFaith(int fai) { 
    faith = fai; 
}
void Stats::setArcane(int arc) { 
    arcane = arc; 
}

// Print stats
void Stats::print() const {
    std::cout << "Level: " << level << std::endl;
    std::cout << "Vigor: " << vigor << ", Mind: " << mind << ", Endurance: " << endurance << std::endl;
    std::cout << "Strength: " << strength << ", Dexterity: " << dexterity << ", Intelligence: " << intelligence << std::endl;
    std::cout << "Faith: " << faith << ", Arcane: " << arcane << std::endl;
}
