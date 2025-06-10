#ifndef MOTOR_H
#define MOTOR_H
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;
//part 1
class Material {
public:
string name;
float density = 0, yieldpoint = 0;  // Density in g/cm³, Yield in MPa
Material() : name(""), density(0), yieldpoint(0) {}                 // Default constructor
Material    (string n, float d, float y) : name(n), density(d), yieldpoint(y) {} // Parameterized constructor
};
class CrossSection {
public:
    string shape;
    float length, width, height, radius;
    float linkmass = 0, density, g = 9.81;
    float payloadmass, angularacceleration;
    float moment = 0, i = 0, maxstress = 0 , t_req = 0 ; 

    CrossSection(string s, float L, float w, float h, float r, float mp, float a, float d , float L_m)
               : shape(s), length(L), width(w), height(h), radius(r),payloadmass(mp), angularacceleration(a), density(d) , linkmass(L_m){}
    void calcMass();
    void calcMoment();
    void calcInertia();
    void calcMaxStress();
    void display();
};
class Optimizer {
public:
void optimize(CrossSection& link, float yieldpoint);
};
Material getMaterial(vector<Material>& materials) {
    int choice = -1;

    while (true) {
        cout << "Choose a material (1-" << materials.size() << ") or 0 to add a new one:\n";
        for (int i = 0; i < materials.size(); i++)
            cout << i + 1 << ". " << materials[i].name << "\n Density: " << materials[i].density
                 << " g/cm^3 , Yield: " << materials[i].yieldpoint << " MPa\n"<<"-----------------------------------------\n";


        // بنشوف ال input نفس ال data type اللي عايزينه ولا لا
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) {
            string n;
            float d, y;
            // بنشوف ال input نفس ال data type اللي عايزينه ولا لا
            while (true) {
                cout << "Enter name, density (kg/m^3), yield strength (MPa): ";
                cin >> n >> d >> y;
                if (cin.fail()) {
                    cout << "Wrong input! Make sure density and yield are numbers.\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                } else {cin.ignore(1000, '\n');

                    break;
                }
            }

            materials.push_back({n, d, y});
            cout << "Your material is: " << n << endl;
            return materials.back();

        } else if (choice >= 1 && choice <= materials.size()) {
            cout << "Your material is: " << materials[choice - 1].name << endl;
            return materials[choice - 1];

        } else {
            cout << "Invalid choice! Please enter a number from 0 to " << materials.size() << ".\n";
        }
    }
}
CrossSection getCrossSection(const Material& mat) {
    string shape;
    float L = 0, w = 0, h = 0, r = 0, mp = 0, a = 0 , t_req = 0;

    // بنشوف ال input نفس ال data type اللي عايزينه ولا لا
    while (true) {
        cout << "Enter cross section shape (rectangle(r)/circle(c)): ";
        cin >> shape;

        if (shape == "r" || shape == "c"||shape == "R" || shape == "C"){
            break;
        } else {
            cout << "Unknown shape! Please enter correct shape (rectangle(r)/circle)." << endl;
        }
    }

    // بنشوف ال input نفس ال data type اللي عايزينه ولا لا
    cout << "Enter link length (m): ";
    while (!(cin >> L)) {
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter link length (m): ";
    }

    cout << "Enter payload mass (kg): ";
    while (!(cin >> mp)) {
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter payload mass (kg): ";
    }

    cout << "Enter max angular acceleration (rad/s^2): ";
    while (!(cin >> a)) {
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Enter max angular acceleration (rad/s^2): ";
    }

    // الأبعاد حسب نوع الشكل
    if (shape == "r"||shape == "R") {
        cout << "Enter initial width (m): ";
        while (!(cin >> w)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter initial width (m): ";
        }
        cout << "Enter initial height (m): ";
        while (!(cin >> h)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter initial height (m): ";
        }
    } else {
        cout << "Enter initial radius (m): ";
        while (!(cin >> r)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter initial radius (m): ";
        }
    }
    return CrossSection(shape, L, w, h, r, mp, a, mat.density , t_req );
}
vector<Material> materials = {
    {"cast iron", 7.3, 130}, 
    {"copper nickel", 8.94, 130}, 
    {"Brass", 8.73, 200},
    {"aluminum", 2.7, 241},
    {"steel", 7.58, 247}, 
    {"Acrylic", 1.16, 72},
    {"copper", 8.92, 70}, 
    {"stainless steel", 7.86, 275}, 
    {"Tungsten", 19.25, 941}};

//part 2
class Motor{
        private:
        string name ;
        double cost ;
        double torque ;
        double efficiency ;
        double diameter ;
        double width ;
        double weight ;
        double speed ;

        public:
        Motor(string n, double e, double w , double d , double wi , double s , double t)
        : name(n), efficiency(e), weight(w), diameter (d), width(wi), speed(s), torque (t)  {}
        string getName() const { return name; }             //getter for name
        double getCost() const { return cost; }             //getter for cost
        double getTorque() const { return torque; }         //getter for torque
        double getEffiecency() const { return efficiency; } //getter for effiecency
        double getDiameter() const { return diameter; }     //getter for diameter
        double getWidth() const { return width; }           //getter for width
        double getspeed() const { return speed; }           //getter for speed
        double getWeight() const { return weight; }         //getter for weight

};
class Gearbox{
private:
    string name;
    double gear_ratio;
    double efficiency;  // 0-1
    double weight;      // kg
    double diameter;    // mm
    double width;       // mm
    double torque;      // Nm

public:
    Gearbox(string n, double gr, double eff, double w, double d, double wi , double t)
        : name(n), gear_ratio(gr), efficiency(eff), weight(w), diameter(d), width(wi) , torque(t) {}
    string getName() const { return name; }              //getter for name
    double getGearRatio() const { return gear_ratio; }   //getter for gear ratio
    double getEfficiency() const { return efficiency; }  //getter for efficiency
    double getWeight() const { return weight; }          //getter for weight
    double getDiameter() const { return diameter; }      //getter for diameter
    double getWidth() const { return width; }            //getter for width
    double getTorque() const { return torque; }          //getter for torque
};
vector<Motor> getExampleMotors() {
vector<Motor> motors;
 //name, efficiency, weight(g), diameter (mm), width(mm), speed(rpm), torque (mNm)
    motors.push_back(Motor("m1", 0.69, 12, 1.5, 13, 9930, 0.499));
    motors.push_back(Motor("M2", 0.49, 15, 1.5, 13, 12600 , 0.194));
    motors.push_back(Motor("M3", 0.67, 7, 1, 10, 1970, 0.792));
    motors.push_back(Motor("M4", 0.55, 22, 1.5, 16, 9040, 0.579));
    motors.push_back(Motor("M5", 0.68, 7, 1, 10, 11400, 0.802));
    motors.push_back(Motor("M6", 0.64, 22, 1.5, 16, 5520, 1.99));
    motors.push_back(Motor("M7", 0.63, 22, 1.5, 16, 6310, 1.24));
    motors.push_back(Motor("M8", 0.76, 21, 1.5, 16, 6700, 2.19));
    motors.push_back(Motor("M9", 0.76, 21, 1.5, 16, 8120, 1.24));
    motors.push_back(Motor("M10", 0.72, 54, 2, 22, 6890, 6.93));
    motors.push_back(Motor("M11", 0.83, 54, 2, 22, 7030, 6));
    motors.push_back(Motor("M12", 0.84, 117, 3, 26, 5050, 15.8));
    motors.push_back(Motor("M13", 0.84, 117, 3, 26, 4970, 11.3));
    motors.push_back(Motor("M14", 0.90, 130, 3, 25, 3710, 28.7));
    motors.push_back(Motor("M15", 0.87, 130, 3, 25, 4520, 20.9));
    motors.push_back(Motor("M16", 0.88, 480, 6, 40, 6380, 94.9));
    motors.push_back(Motor("M17", 0.80, 305, 4, 30, 6590, 63.6));
    motors.push_back(Motor("M18", 0.83, 720, 6, 40, 6280, 185));
    motors.push_back(Motor("M19", 0.88, 325, 6, 32, 8070, 101));
    motors.push_back(Motor("M20", 0.84, 375, 8, 60, 2790, 496));
    motors.push_back(Motor("M21", 0.82, 720, 6, 40, 3770, 203));
    motors.push_back(Motor("M22", 0.83, 2100, 12, 65, 3810, 501));
    motors.push_back(Motor("M23", 0.90, 752, 8, 52, 3800, 972));
    motors.push_back(Motor("M24", 0.93, 1595, 14, 70, 4090, 1520));
    motors.push_back(Motor("M25", 0.93,  2295, 14, 70, 3140, 2480));

    return motors;
}
vector<Gearbox> getExampleGearboxes() {
vector<Gearbox> gearboxes;
    //name , gear_ratio, efficiency, weight(g), diameter(mm), width(mm) , torque (Nm)
    gearboxes.push_back(Gearbox("g1 ", 3.9/1 , 0.88, 2, 1.5, 6 , 0.002));
    gearboxes.push_back(Gearbox("g2 ", 	17/1 , 0.76, 1, 1.45, 4 , 0.002));
    gearboxes.push_back(Gearbox("g3 ", 854/1 , 0.52, 3 , 1.5, 6 , 0.03));
    gearboxes.push_back(Gearbox("g4 ", 	1024/1 , 0.59, 5, 1.5, 8 , 0.1));
    gearboxes.push_back(Gearbox("g5 ", 36/1 , 0.76, 3, 1.3, 8 , 0.008 ));
    gearboxes.push_back(Gearbox("g6 ", 256/1 , 0.65, 8, 1.8, 10 , 0.15));
    gearboxes.push_back(Gearbox("g7 ", 261/1 , 0.59, 9, 1.5, 12 , 0.025));
    gearboxes.push_back(Gearbox("g8 ", 	1119/1 , 0.62, 23, 1.5, 13 , 0.53));
    gearboxes.push_back(Gearbox("g9 ", 35/1 , 0.80, 19, 3, 14 , 0.2));
    gearboxes.push_back(Gearbox("g10 ", 561/1 , 0.65, 26, 2, 16 , 0.25));
    gearboxes.push_back(Gearbox("g11 ", 243/1 , 0.65, 55, 4, 19 , 0.8));
    gearboxes.push_back(Gearbox("g12 ", 280/1 , 0.65, 1, 1.5, 4 , 0.015));
    gearboxes.push_back(Gearbox("g13 ", 590/1 , 0.87, 115, 5.5, 19 , 5.2));
    gearboxes.push_back(Gearbox("g14 ", 64/1 , 0.66, 28, 3, 24 , 0.1));
    gearboxes.push_back(Gearbox("g15 ", 679/1 , 0.55, 153, 8, 26 , 6.3));
    gearboxes.push_back(Gearbox("g16 ", 679/1 , 0.87, 357, 10, 32 , 12.6));
    gearboxes.push_back(Gearbox("g17 ", 186/1 , 0.75, 410,10,37,9.3));
    return gearboxes;
}
class calculations {
    double ML, L, mp, A_max;
    public:
    calculations(const CrossSection& link): ML(link.linkmass), L(link.length), mp(link.payloadmass), A_max(link.angularacceleration) {}
    void get_Required_motor();
};

#endif