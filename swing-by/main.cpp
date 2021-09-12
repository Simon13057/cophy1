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

    // Parameter: runtime, step
    LeapFrog sol(10.0, 0.001);
    // Warning: leapfrog_2obj changes vals of second Object (param is a reference)
    //sol.leapfrog_2obj(first, second);

    double vges = sqrt(second.vx * second.vx + second.vy * second.vy);
    sol.max_vges(first, second.x, second.y, vges, second.get_m(), second.get_radius());

    cout << "DONE" << endl;
    return 0;
}
