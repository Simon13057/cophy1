#include "object.h"
#include "solve.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    // Parameter: x, y, vx, vy, mass, radius
    Object first(0., 50., 0., -10., 100., 10.);
    Object second(300., 0., -50., 0., 1., 1.);

    // Parameter: runtime, step, filename
    LeapFrog sol(10.0, 0.001, "some_data.csv");
    //sol.leapfrog_2obj(first, second);

    double vges = sqrt(second.vx * second.vx + second.vy * second.vy);
    double phi_max = sol.max_vges(first, second.x, second.y, vges, second.get_m(), second.get_radius());

    double vx = sin(phi_max) * vges;
    double vy = cos(phi_max) * vges;
    cout << vx << " - " << vy << endl;
    //Object first_max(0., 0., 0., -5., 100.);
    //Object second_max(30., 0., vx, vy, 1.);
    //sol.leapfrog_2obj(first_max, second_max);

    cout << "DONE" << endl;
    return 0;
}
