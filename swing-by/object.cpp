#include "object.h"

using namespace std;

void Object::set_mass(double m)
{
    mass = m;
}

Object::Object()
{
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    mass = 1;
    cout << "created new default object" << endl;
}

Object::Object(double x, double y, double vx, double vy, double m)
{
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    mass = m;
    cout << "created new object" << endl;
}
