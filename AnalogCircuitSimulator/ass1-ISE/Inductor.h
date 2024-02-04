// Inductor.h - derived class for an Inductor
// Written by Tasbi Tasbi

#ifndef _INDUCTOR_H_
#define _INDUCTOR_H_

#include "Component.h"

class Inductor : public Component {
private:
    float inductance;
public:
    double voltage;
    double currentPrevious;
    Inductor(float _Inductance, float _Red, float _Green, float _Blue, const std::string& _name);
    std::string GetName() const;
    void Update(double newCurrent, double newVoltage);
    double GetVoltage(double _current, double timestep);
    void Display(int xpos, int ypos);
    float getRed();
    float getGreen();
    float getBlue();
};

#endif // _INDUCTOR_H_