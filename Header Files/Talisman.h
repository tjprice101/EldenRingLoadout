#ifndef TALISMAN_H
#define TALISMAN_H

#include <string>
#include <iostream>

class Talisman {
private:
    std::string name;

public:
    // Constructor
    Talisman(const std::string& name);

    // Getter
    std::string getName() const;

    // Setter
    void setName(const std::string& newName);

    // Print info
    void print() const;
};

#endif
