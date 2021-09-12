#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>
#include <math.h>

using namespace std;

class Object
{
private:
    double mass, radius;

public:
    double x, y, vx, vy;

    Object();
    Object(double, double, double, double, double, double);

    string print_vals() { return to_string(this->x) + ";" + to_string(this->y) + ";" + to_string(this->vx) + ";" + to_string(this->vy) + ";"; };
    double get_vges() { return sqrt(vx * vx + vy * vy); };
    void set_mass(double);
    double get_m() { return mass; };
    void set_radius(double);
    double get_radius() { return radius; };
    double get_kinE() { return 0.5 * this->get_m() * this->get_vges() * this->get_vges(); };
};

#endif