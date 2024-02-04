//AnalogCircuit.cpp - function definitions for the analog circuit
//
// 20-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.
// 27-Oct-23  Madhur Saluja, Mohammed Aeraf Khan, Tasbi Tasbi added code in run function
// 28-Oct-23  Madhur Saluja, Mohammed Aeraf Khan, Tasbi Tasbi added code in the cost function

#include <iomanip>//setw
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>//M_PI
#include <stdlib.h>//abs

#include "AnalogCircuit.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Resistor.h"

using namespace std;

int xpos, ypos;
int windowWidth, windowHeight;
double scalingFactor;

void start() {
	cout << "BEGIN" << endl;
	AnalogCircuit circuit("RLC.dat");
	circuit.run();
	cout << "Press any key + ENTER to end..." << endl;
	char key;
	cin >> key;
	glutLeaveMainLoop();
	cout << "DONE!" << endl;
}

void AnalogCircuit::display(float R, float G, float B) {//draw a point on the screen
	//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(static_cast<GLfloat>(xpos), static_cast<GLfloat>(ypos));
	glEnd();
	glFlush();
}

AnalogCircuit::AnalogCircuit(std::string filename) {
	// Initialize your circuit and data file handling here
	// For example, open the data file for writing
	fout.open(filename);
	if (!fout.is_open()) {
		std::cerr << "Failed to open data file." << std::endl;
	}
}


void AnalogCircuit::run() {
	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red

	// Constants for drawing lines
	const double horizontalLineY = scalingFactor * windowHeight / 2.0;
	const double verticalLineX = xoffset;

	// Drawing horizontal line
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0); 
	glVertex2f(verticalLineX, horizontalLineY);
	glVertex2f(windowWidth, horizontalLineY);
	glEnd();
	glFlush();

	// Drawing vertical line
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);  
	glVertex2f(verticalLineX, 0);
	glVertex2f(verticalLineX, scalingFactor * windowHeight);
	glEnd();
	glFlush();

	// Drawing horizontal line markers
	const int numHorizontalMarkers = 12; // need 12 markers
	const float horizontalMarkerInterval = windowHeight * scalingFactor / numHorizontalMarkers;		// markers effectively at an interval of 50 units (pixel?)

	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0); // White color for lines
	for (int i = 1; i < numHorizontalMarkers; ++i) {
		float y = i * horizontalMarkerInterval;
		glVertex2f(verticalLineX - 5, y); // Start point (5 units to the left of the vertical line)
		glVertex2f(verticalLineX + 5, y); // End point (5 units to the right of the vertical line)
	}
	glEnd();
	glFlush();

	// Drawing vertical line markers	( we might need to change this later on)
	const int numVerticalMarkers = 9; // need 9 markers
	const float verticalMarkerInterval = windowWidth / (numVerticalMarkers + 1);

	glBegin(GL_LINES);
	for (int i = 1; i <= numVerticalMarkers; ++i) {
		float x = (i * verticalMarkerInterval) + verticalLineX;
		// Draw small markers above the horizontal line
		glVertex2f(x, horizontalLineY + 5); // Start point (5 units above the horizontal line)
		glVertex2f(x, horizontalLineY - 5); // End point (5 units below the horizontal line)
	}
	glEnd();
	glFlush();

	glClearColor(0.0, 0.0, 0.0, 1.0);  // clear background with black


	//Displaying each component's name and colour

	int legendX = 2;					// X position of the legend
	int legendY = windowHeight - 30;	// Y position of the legend

	// Iterating through the components and displaying their names and colors
	for (const auto& comp : component) {
		glColor3f(1.0, 1.0, 1.0);		// Set color for the name to white
		glRasterPos2f(legendX, legendY);
		for (const char c : comp->GetName()) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
		}
		glFlush();

		// Drawing a small line in the component's color in front of the name
		glColor3f(comp->getRed(), comp->getGreen(), comp->getBlue());
		glBegin(GL_LINES);
		glVertex2f(legendX + 25, legendY);   // Start point of the line
		glVertex2f(legendX + 15, legendY);   // End point of the line
		glEnd();
		glFlush();

		// Move down for the next legend entry
		legendY -= 20;
	}
	glFlush();

	//Run the simulation for the first 0.06 seconds (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	glColor3f(1.0, 1.0, 1.0);
	for (double time = 0.0; time < 0.6 * timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);
		
		fout << std::fixed << std::setprecision(7) << setw(12) << time;
		fout << std::fixed << std::setprecision(7) << setw(12) << V;

		xpos = ((scalingFactor * windowWidth * time / (0.6 * timeMax)/2) + verticalLineX);
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;

		display(1.0, 1.0, 1.0);		// displaying "V" (voltage)
		CostFunctionV(I, V);
	}

	//Run the simulation to the end (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.6 * timeMax; time < timeMax; time += T) {
		double V = 0.0;

		fout << std::fixed << std::setprecision(7) << setw(12) << time;
		fout << std::fixed << std::setprecision(7) << setw(12) << V;

		xpos = ((scalingFactor * windowWidth * time / (0.6 * timeMax) / 2) + verticalLineX);
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;

		CostFunctionV(I, V);
	}
}


void AnalogCircuit::CostFunctionV(double& current, double voltage) {
	double I1 = current;
	double J1 = 0.0;
	double J0 = 0.0;
	double alpha = 1.0;
	double compVoltage = 0;

	do {
		double sumVoltage = 0.0;
		list<Component*>::iterator it;
		for (it = component.begin(); it != component.end(); ++it) {
			double Vcomponent = (*it)->GetVoltage(I1, T);
			sumVoltage += Vcomponent;
		}
		J1 = sumVoltage - voltage;
		//Reduce alpha if J1 and J0 are of opposite signs or are equal to each other
		if ((abs(J0 - J1) != (J0 - J1)) || J0 == J1)alpha /= 2.0;

		if (abs(J1) > tolerance) {
			if (J1 < 0) {//increase the current
				I1 += alpha;
			}
			else {
				I1 -= alpha;
			}
			J0 = J1;
		}
		if (alpha < tolerance / 1000000.0) {//reset alpha
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;//between 0.5 and 1.5
		}
	} while (abs(J1) > tolerance);

	fout << setw(12) << I1;
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		compVoltage = (*it)->GetVoltage(I1, T);
		fout << std::fixed << std::setprecision(7) << setw(12) << compVoltage;
		ypos = (windowHeight * compVoltage / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		(*it)->Display(xpos, ypos);
		(*it)->Update(I1, compVoltage);	// I1 being the new current, and get
	}
	fout << endl;

	current = I1;
}

AnalogCircuit::~AnalogCircuit() {//perform cleanup
	if (fout.is_open()) {
		fout.close();	// close the file
	}
	
	for (auto comp : component) {
		delete comp;	// Deallocating dynamically allocated memory
	}
}