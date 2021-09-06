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
    string filename;

    LeapFrog();
    LeapFrog(double, double, string);

    void leapfrog_fixedObj(Object &, Object &);
    void leapfrog_2obj(Object, Object &);
    double max_vges(Object, double, double, double, double, double);
};

double *f(double[]);

#endif