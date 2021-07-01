#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define H 0.01
#define MAX 30

double F(double r)
{
    return -r*exp(-r)/2; // times 1/(4 pi epsilon)
}

double k(double r)
{
    return 0;
}

int main()
{
    double r = MAX;

    //set inital values
    double chi = 0;
    double chi_prime = 0;
    double chi_n_minus_one = H;
    double chi_n_plus_one;

    while(r > 0)
    {
        chi_n_plus_one = H*H/12*(F(r-H) + 10*F(r) + F(r+H)) + 2*chi - chi_n_minus_one;

        printf("%g %g %g\n", r, chi, chi_n_plus_one);
        chi = chi_n_plus_one;

        r -= H;
    }
    return 0;
}
