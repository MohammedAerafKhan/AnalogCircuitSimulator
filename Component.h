//Component.h - abstract base class for electronic components

// 19-May-22  M. Watler				Created.
// 27-May-22  M. Watler				Added graphical display.
// 23-Oct-23  T. Tasbi				Added getRed, getBlue and getGreen functions
// 24-Oct-23  K. Mohammed Aeraf		Changed getVoltage and display function
// 24-Oct-23  S. Madhur				CHanged Update function

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>


class Component {
protected:
	float Red;
	float Green;
	float Blue;
	std::string name;
public:
	virtual std::string GetName() const = 0;
	virtual void Update(double newCurrent, double newVoltage) = 0;
	virtual double GetVoltage(double _current, double timestep) = 0;
	virtual void Display(int xpos, int ypos) = 0;
	virtual float getRed() = 0;
	virtual float getBlue() = 0;
	virtual float getGreen() = 0;
};

#endif// _COMPONENT_H_