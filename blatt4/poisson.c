#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define H 0.001
#define MAX 20

double F(double x)
{
    return -x*exp(-x)/2.; // 1/(4*M_PI*EPS0)
}

int main()
{
    //set inital values
    double f_n = H;
    double f_np = 0; //f n+1
    double f_nm;     //f n-1

    for (double x = MAX; x > 0; x -= H)
    {
        f_nm = H*H/12*(F(x-H) + 10*F(x) + F(x+H)) + 2*f_n - f_np;

        printf("%g %g %g\n", x, f_nm, f_nm + x - 19);

        f_np = f_n;
        f_n = f_nm;
    }

    return 0;
}
