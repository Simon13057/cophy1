#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define H 0.001 // step size
#define MAX 20  // maximum distance

double F(double x)
{
    return -x*exp(-x)/2.; // 1/(4*M_PI*EPS0)
}

int main()
{
    //set inital values
    double f_n = 1-H;
    double f_nm = 1; //f n-1
    double f_np;     //f n+1

    for (double x = MAX; x > 0; x -= H)
    {
        printf("%g %g %g\n", x, f_n, f_n - x + 20);

        f_np = H*H/12*(F(x-H) + 10*F(x) + F(x+H)) + 2*f_n - f_nm;

        f_nm = f_n;
        f_n = f_np;
    }

    return 0;
}
