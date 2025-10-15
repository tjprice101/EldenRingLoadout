#include "Weapon.h"

// Constructor 
Weapon::Weapon(const std::string& wName, const std::string& wAshOfWar, const std::string& wAffinity, int wLevel) {
    name = wName;
    ashOfWar = wAshOfWar;
    affinity = wAffinity;
    level = wLevel;
}

// Getters
std::string Weapon::getName() const { 
    return name; 
}

std::string Weapon::getAshOfWar() const { 
    return ashOfWar; 

}
std::string Weapon::getAffinity() const { 
    return affinity; 
}
int Weapon::getLevel() const { 
    return level; 
}

// Setters
void Weapon::setName(const std::string& newName) { 
    name = newName; 
}
void Weapon::setAshOfWar(const std::string& newAsh) { 
    ashOfWar = newAsh; 
}

void Weapon::setAffinity(const std::string& newAffinity) { 
    affinity = newAffinity;
}

void Weapon::setLevel(int newLevel) { 
    level = newLevel; 
}

// Print weapon info
void Weapon::print() const {
    std::cout << "Weapon: " << name 
              << ", Ash of War: " << ashOfWar 
              << ", Affinity: " << affinity 
              << ", Level: " << level << std::endl;
}
