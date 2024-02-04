// Written by Tasbi Tasbi

#include "Inductor.h"
#include "AnalogCircuit.h"

Inductor::Inductor(float _Inductance, float _Red, float _Green, float _Blue, const std::string& _name) {
    Red = _Red;
    Green = _Green;
    Blue = _Blue;
    name = _name;
    inductance = _Inductance;
    currentPrevious = 0;
}

std::string Inductor::GetName() const {
    return name;
}

void Inductor::Update(double newCurrent, double newVoltage) {
    currentPrevious = newCurrent;   // current[0] = current[1]
}

double Inductor::GetVoltage(double _current, double timestep) {
    return (inductance * (_current - currentPrevious) / timestep);
}

void Inductor::Display(int xpos, int ypos) {
    glColor3f(getRed(), getGreen(), getBlue());
    glBegin(GL_POINTS);
    glVertex2f((xpos), (ypos));
    glEnd();
    glFlush();
}

float Inductor::getRed() {
    return this->Red;
}

float Inductor::getBlue() {
    return this->Blue;
}

float Inductor::getGreen() {
    return this->Green;
}