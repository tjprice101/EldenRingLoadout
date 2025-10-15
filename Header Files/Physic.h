#ifndef PHYSIC_H
#define PHYSIC_H

#include <string>
#include <iostream>

class Physic {
private:
    std::string bubbleTear1;
    std::string bubbleTear2;

public:
    // Constructor
    Physic(const std::string& b1, const std::string& b2);

    // Getters
    std::string getBubbleTear1() const;
    std::string getBubbleTear2() const;

    // Setters
    void setBubbleTear1(const std::string& newB1);
    void setBubbleTear2(const std::string& newB2);

    // Print info
    void print() const;
};

#endif
