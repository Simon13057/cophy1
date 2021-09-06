#include "object.h"

using namespace std;

void Object::set_mass(double m)
{
    mass = m;
}

void Object::set_radius(double m)
{
    radius = m;
}

Object::Object()
{
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    mass = 1;
    radius = 0;
    cout << "created new default object" << endl;
}

Object::Object(double x, double y, double vx, double vy, double m, double rad)
{
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    mass = m;
    radius = rad;
    cout << "created new object" << endl;
}
