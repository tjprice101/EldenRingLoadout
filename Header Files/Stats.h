#ifndef STATS_H
#define STATS_H

#include <iostream>

class Stats {
private:
    int level;
    int vigor;
    int mind;
    int endurance;
    int strength;
    int dexterity;
    int intelligence;
    int faith;
    int arcane;

public:
    // Constructor
    Stats(int lvl, int vig, int min, int end, int str, int dex, int intl, int fai, int arc);

    // Getters
    int getLevel() const;
    int getVigor() const;
    int getMind() const;
    int getEndurance() const;
    int getStrength() const;
    int getDexterity() const;
    int getIntelligence() const;
    int getFaith() const;
    int getArcane() const;

    // Setters
    void setLevel(int lvl);
    void setVigor(int vig);
    void setMind(int min);
    void setEndurance(int end);
    void setStrength(int str);
    void setDexterity(int dex);
    void setIntelligence(int intl);
    void setFaith(int fai);
    void setArcane(int arc);

    // Print stats
    void print() const;
};

#endif
