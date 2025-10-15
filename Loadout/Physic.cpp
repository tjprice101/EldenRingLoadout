#include "Physic.h"

// Constructor
Physic::Physic(const std::string& b1, const std::string& b2) {
    bubbleTear1 = b1;
    bubbleTear2 = b2;
}

// Getters
std::string Physic::getBubbleTear1() const { 
    return bubbleTear1; 
}
std::string Physic::getBubbleTear2() const { 
    return bubbleTear2; 
}

// Setters
void Physic::setBubbleTear1(const std::string& newB1) { 
    bubbleTear1 = newB1; 
}
void Physic::setBubbleTear2(const std::string& newB2) { 
    bubbleTear2 = newB2; 
}

// Print info
void Physic::print() const {
    std::cout << "Physic: Bubble Tear 1 = " << bubbleTear1
              << ", Bubble Tear 2 = " << bubbleTear2 << std::endl;
}
