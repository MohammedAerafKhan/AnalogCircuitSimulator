// Capacitor.h - derived class for a capacitor
// Written By Mohammed Aeraf Khan

#ifndef _CAPACITOR_H_
#define _CAPACITOR_H_

#include "Component.h"

class Capacitor : public Component {
private:
    float capacitance;
public:
    double voltage;
    double voltagePrevious;
    Capacitor(float _Capacitance, float _Red, float _Green, float _Blue, const std::string& _name);
    std::string GetName() const;
    void Update(double newCurrent, double newVoltage);
    double GetVoltage(double _current, double timestep);
    void Display(int xpos, int ypos);
    float getRed();
    float getGreen();
    float getBlue();
};

#endif // _CAPACITOR_H_