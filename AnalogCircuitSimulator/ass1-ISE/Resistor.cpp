// Written by Madhur Saluja

#include "Resistor.h"
#include "AnalogCircuit.h"

Resistor::Resistor(float _Resistance, float _Red, float _Green, float _Blue, const std::string& _name) {
    Red = _Red;
    Green = _Green;
    Blue = _Blue;
    name = _name;
    resistance = _Resistance;
}

std::string Resistor::GetName() const {
    return name;
}

void Resistor::Update(double newCurrent, double newVoltage) {
    // resistor doesn't need to update anything.
}

double Resistor::GetVoltage(double _current, double timestep) {
    return _current * resistance;
}

void Resistor::Display(int xpos, int ypos) {
    glColor3f(getRed(), getGreen(), getBlue());
    glBegin(GL_POINTS);
    glVertex2f(xpos, ypos);
    glEnd();
    glFlush();
}

float Resistor::getRed() {
    return this->Red;
}

float Resistor::getBlue() {
    return this->Blue;
}

float Resistor::getGreen() {
    return this->Green;
}
