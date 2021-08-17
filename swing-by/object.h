#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>

using namespace std;

class Object
{
    double mass;

public:
    double x, y, vx, vy;

    Object();
    Object(double, double, double, double, double);

    string print_vals() { return to_string(this->x) + ";" + to_string(this->y) + ";" + to_string(this->vx) + ";" + to_string(this->vy) + ";"; };
    void set_mass(double);
    double get_m() { return mass; };
};

#endif
