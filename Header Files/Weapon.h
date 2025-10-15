#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

class Weapon {
private:
    std::string name;
    std::string ashOfWar;
    std::string affinity;
    int level;

public:
    // Constructor
    Weapon(const std::string& name, const std::string& ashOfWar, const std::string& affinity, int level);

    // Getters 
    std::string getName() const;
    std::string getAshOfWar() const;
    std::string getAffinity() const;
    int getLevel() const;

    // Setters
    void setName(const std::string& newName);
    void setAshOfWar(const std::string& newAsh);
    void setAffinity(const std::string& newAffinity);
    void setLevel(int newLevel);

    // Print weapon info
    void print() const;
};

#endif
