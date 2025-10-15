#ifndef SPELL_H
#define SPELL_H

#include <string>
#include <iostream>

class Spell {
private:
    std::string name;

public:
    // Constructor
    Spell(const std::string& name);

    // Getters
    std::string getName() const;

    // Setters
    void setName(const std::string& newName);

    // Print info
    void print() const;
};

#endif
