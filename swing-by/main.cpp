#include "object.h"
#include "solve.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    Object first(0., 0., 5., 0., 10000.);
    Object second(15., 0., 0., 30., 10);

    if (argc == 11)
    {
        first.x = atof(argv[1]);
        first.y = atof(argv[2]);
        first.vx = atof(argv[3]);
        first.vy = atof(argv[4]);
        double tempMass = atof(argv[5]);
        first.set_mass(tempMass);

        second.x = atof(argv[6]);
        second.y = atof(argv[7]);
        second.vx = atof(argv[8]);
        second.vy = atof(argv[9]);
        tempMass = atof(argv[10]);
        second.set_mass(tempMass);
    }

    LeapFrog sol(30.0, 0.001, "some_data.csv");
    sol.leapfrog_2obj(first, second);

    cout << "DONE" << endl;
    return 0;
}
