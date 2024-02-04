// Resistor.h - derived class for a resistor
// Written by Madhur Saluja

#ifndef _RESISTOR_H_
#define _RESISTOR_H_

#include "Component.h"

class Resistor : public Component {
private:
    float resistance;
public:
    double voltage;
    Resistor(float _Resistance, float _Red, float _Green, float _Blue, const std::string& _name);
    std::string GetName() const;
    void Update(double newCurrent, double newVoltage);
    double GetVoltage(double _current, double timestep);
    void Display(int xpos, int ypos);
    float getRed();
    float getGreen();
    float getBlue();
};

#endif  //_RESISTOR_H_