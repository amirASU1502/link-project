#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "motor.h"

using namespace std;


//part 1
void CrossSection::calcMass() {
        if (shape == "r" || shape == "R"){
            linkmass = (density * width * height * length) ; 
        }
        else if (shape == "c" || shape=="C")
            linkmass = (density * M_PI * pow(radius, 2) * length) ;  
        else
            cout << "Unknown shape! " << endl;
    }
void CrossSection::calcMoment() {
        calcMass();
        moment = linkmass * g * (length / (2))
               + payloadmass * g * (length)
               + linkmass * pow(length / (2) , 2) * angularacceleration
               + payloadmass * pow(length, 2) * angularacceleration;
    }
void CrossSection::calcInertia() {
        if (shape == "r" || shape == "R")
            i = (width * pow(height, 3)) / 12;
        else if (shape == "c" || shape=="C")
            i = (M_PI * pow(radius, 4)) / 4;
        else
            cout << "Unknown shape!" << endl;
    }
void CrossSection::calcMaxStress() {
        calcMoment();
        calcInertia();
        if (shape == "r" || shape == "R")
            maxstress = (moment * height) / (2 * i);
        else if (shape == "c" || shape=="C")
            maxstress = (moment * radius) / i;
    }
void CrossSection::display() {
        if (shape == "r" || shape == "R")
            cout << "Optimized Width: " << width << " m, Height: " << height << " m\n";
        else if (shape == "c" || shape=="C")
            cout << "Optimized Radius: " << radius << " m\n";
    cout << "Final Stress: " << maxstress << " MPa\n";
    cout << "Final Mass: " << linkmass << " kg\n";
    }
void Optimizer::optimize(CrossSection& link, float yieldpoint) {
        link.calcMaxStress();

        // Increase size until stress < yield
        while (link.maxstress > yieldpoint) {
            if (link.shape == "r"||link.shape == "R") {
                link.width *= 1.01;
                link.height *= 1.01;
            } 
            else {
                link.radius *= 1.01;
            }
            link.calcMaxStress();
        }
        // Reduce size to get closer to 99% of yield strength
        while (link.maxstress < yieldpoint * 0.99) {
            float prevWidth = link.width, prevHeight = link.height, prevRadius = link.radius;
            if (link.shape == "r"||link.shape == "R") {
                link.width *= 0.99;
                link.height *= 0.99;
            } else {
                link.radius *= 0.99;
            }
            link.calcMaxStress();

            if (link.maxstress > yieldpoint) {
                if (link.shape == "r"||link.shape == "R") {
                    link.width = prevWidth;
                    link.height = prevHeight;
                } 
                else {
                    link.radius = prevRadius;
                }
                link.calcMaxStress();
                break;
            }
        }
        link.display();
    }

//part 2 
void calculations::get_Required_motor() {
    double speed_required;
    cout << "Enter required speed (rad/s): ";
    while (!(cin >> speed_required)) {
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter required speed (rad/s): ";
    }

    // Ask user for optimization priority
    int priority;
    cout << "\nChoose optimization priority:\n"
         << "1 - Minimize Mass\n"
         << "2 - Minimize Cost (Mass + Diameter/100 + Width/100)\n"
         << "Enter choice (1 or 2): ";
    while (!(cin >> priority) || (priority != 1 && priority != 2)) {
        cout << "Invalid input! Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter choice (1 or 2): ";
    }

    double g = 9.81;
    double t_req = ML * g * (L / 2) + mp * g * L + ML * pow(L / 2, 2) * A_max + mp * pow(L, 2) * A_max;

    vector<Motor> motors = getExampleMotors();
    vector<Gearbox> gearboxes = getExampleGearboxes();

    double bestScore = numeric_limits<double>::max();
    string bestMotor, bestGearbox;
    double bestTorque = 0, bestSpeed = 0;

    for (const auto& motor : motors) {
        for (const auto& gearbox : gearboxes) {
            double outputTorque = motor.getTorque() * gearbox.getGearRatio() * gearbox.getEfficiency();
            double outputSpeed = motor.getspeed() / gearbox.getGearRatio();

            if (outputTorque >= t_req && outputSpeed >= speed_required) {
                // Calculate score based on user's priority
                double score;
                if (priority == 1) { // minimize mass
                    score = motor.getWeight() + gearbox.getWeight();
                } else { // minimize cost (mass + diameter/100 + width/100)
                    score = motor.getWeight() + motor.getDiameter() / 100 + motor.getWidth() / 100
                          + gearbox.getWeight() + gearbox.getDiameter() / 100 + gearbox.getWidth() / 100;
                }

                if (score < bestScore) {
                    bestScore = score;
                    bestMotor = motor.getName();
                    bestGearbox = gearbox.getName();
                    bestTorque = outputTorque;
                    bestSpeed = outputSpeed;
                }
            }
        }
    }

    if (bestScore < numeric_limits<double>::max()) {
        cout << "\nBest Motor-Gearbox Combination:\n";
        cout << "Motor: " << bestMotor << "\n";
        cout << "Gearbox: " << bestGearbox << "\n";
        cout << "Output Torque: " << bestTorque << " Nm\n";
        cout << "Output Speed: " << bestSpeed << " rad/s\n";
        cout << "required torque: " << t_req << " Nm\n";
        cout << "required speed: " << speed_required << " rad/s\n";
        if (priority == 1)
            cout << "Total Mass: " << bestScore << " kg\n";
        else
            cout << "Cost Score: " << bestScore << "\n";
    } else {
        cout << "\n No suitable motor-gearbox combination found.\n";
    }
}
