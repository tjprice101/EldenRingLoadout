#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include <iostream>

class Armor {
private:
    std::string typeOfArmor;
    std::string name;

public:
    // Constructor
    Armor(const std::string& typeOfArmor, const std::string& name);

    // Getters
    std::string getTypeOfArmor() const;
    std::string getName() const;

    // Setters
    void setTypeOfArmor(const std::string& newType);
    void setName(const std::string& newName);

    // Print info
    void print() const;
};

#endif
