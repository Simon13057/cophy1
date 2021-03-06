#ifndef SOLVE_H
#define SOLVE_H

#include "object.h"
#include <iostream>
#include <math.h>
#include <fstream>

class LeapFrog
{
public:
    double runtime, h;

    LeapFrog();
    LeapFrog(double, double);

    void leapfrog_2obj(Object, Object &);
    double max_vges(Object, double, double, double, double, double);
};

double *f(double[]);

#endif