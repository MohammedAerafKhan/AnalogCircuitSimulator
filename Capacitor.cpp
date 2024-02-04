#include "Capacitor.h"
#include "AnalogCircuit.h"

Capacitor::Capacitor(float _Capacitance, float _Red, float _Green, float _Blue, const std::string& _name) {
    Red = _Red;
    Green = _Green;
    Blue = _Blue;
    name = _name;
    capacitance = _Capacitance;
    voltagePrevious = 0;
}

std::string Capacitor::GetName() const {
    return name;
}

void Capacitor::Update(double newCurrent, double newVoltage) {
    voltagePrevious = newVoltage;   // voltage[0] = voltage[1]
}

double Capacitor::GetVoltage(double _current, double timestep) {
    return voltagePrevious + (_current * timestep) / capacitance;;
}

void Capacitor::Display(int xpos, int ypos) {
    glColor3f(getRed(), getGreen(), getBlue());
    glBegin(GL_POINTS);
    glVertex2f(static_cast<GLfloat>(xpos), static_cast<GLfloat>(ypos));
    glEnd();
    glFlush();
}

float Capacitor::getRed() {
    return this->Red;
}

float Capacitor::getBlue() {
    return this->Blue;
}

float Capacitor::getGreen() {
    return this->Green;
}