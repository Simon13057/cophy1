#include "object.h"
#include "solve.h"
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int main()
{
    Object first(0., 0., 0., 1., 100.);
    Object second(1., 0., 5., 10., 10);

    LeapFrog sol(30.0, 0.001, "some_data.csv");
    sol.leapfrog_2obj(first, second);

    cout << "DONE" << endl;
    return 0;
}
