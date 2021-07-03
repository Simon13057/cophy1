/**
 * Solves the schroedinger equation numerically
 * using the numerov method 
 * and the shooting method (to calculate the energy levels)
 * for a linear potential energy box (V(x) = x for x>=0 and V(x) = infty for x<0)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

//#define plank 6.63*pow(10,-34)/2.*M_PI
#define plank 1
#define mass 1
#define h 0.001

using namespace std;

/**
*   Calculates solution using numerov method given the starting values
*   Writes Solution into "e1.dat" file
*   @param values starting values
*/
void numerov(double values[]){
    double fold = values[0], f = values[1], energy = values[2], xmax = values[3];

    double data[int(xmax/h)][2];
    data[0][0] = xmax;
    data[0][1] = fold;

    double fnew = 0.0, knew = 0.0;
    // Spezifisches Potential eingesetzt:
    double kold = 2*mass*(energy-xmax)/pow(plank, 2);
    double k = 2*mass*(energy-(xmax-h))/pow(plank, 2);

    int i = 1;
    for(double x = xmax - h; x > 0; x-=h){
        knew = 2*mass*(energy-(x-h))/pow(plank, 2);
        fnew = (f * (2.-(5./6.)*h*h*k) - fold * (1 + (1./12.)*h*h*kold))/(1 + (1./12.)*h*h*knew);

        data[i][0] = x;
        data[i][1] = f;
        i += 1;

        fold = f;
        f = fnew;
        kold = k;
        k = knew;
    }
    // Norm
    double sum = 0.0;
    for(int j = 0; j < int(xmax/h); j++){
        sum += data[j][1] * data[j][1] * h;
    }

    ofstream file ("e1.dat");
    if(file.fail()){
        cout << "Error with File" << endl;
        return;
    }
    for(int j = 0; j < int(xmax/h); j++){
        file << data[j][0] << " " << data[j][1]/sqrt(sum) << " " << energy << "\n";
    }
    file.close();
}

/**
*   Calculates solution f using numerov method given the starting values
*   @param values starting values
*   @return f(0) 
*/
double diffNumerov(double values[]){
    double fold = values[0], f = values[1], energy = values[2], xmax = values[3];

    double fnew = 0.0, knew = 0.0;
    double kold = 2*mass*(energy-xmax)/pow(plank, 2);
    double k = 2*mass*(energy-(xmax-h))/pow(plank, 2);

    double sum = 0.0; 
    for(double x = xmax - h; x > 0; x-=h){
        knew = 2*mass*(energy-(x-h))/pow(plank, 2);
        fnew = (f * (2.-(5./6.)*h*h*k) - fold * (1 + (1./12.)*h*h*kold))/(1 + (1./12.)*h*h*knew);

        sum += f*f*h;

        fold = f;
        f = fnew;
        kold = k;
        k = knew;
    }

    return f/sum;
}

/**
*   Print energy in console if sign changes (to get intervall next to zeropoints)
*   @param values starting values
*/
void tF(double values[]){
    double E0 = 0.1, E1 = 10.;
    int sign = 1;
    values[2] = E0;
    if(diffNumerov(values) < 0){
        sign = -1;
    }
    double temp;
    for(double E = E0; E < E1; E += h){
        values[2] = E;
        temp = diffNumerov(values);
        if(sign * temp < 0){
            sign = sign*(-1);
            cout << "->" << E << endl;
        }
    }
}

int main(){
    double startVal[] = {0.0,h,7.0,10.0};
    tF(startVal);

    // Calculate zeropoint between given E0 and E1
    double E0=6.2, E1=6.4, Ex, tmp;
    do {
		Ex = (E1+E0)/2.0;
		// bisection (non continous !)
        startVal[2] = Ex;
		tmp = diffNumerov(startVal);

        startVal[2] = E0;
		if(tmp*diffNumerov(startVal)>0)
			E0=Ex;
		else
			E1=Ex;
	} while (fabs((E1-E0)/E0)>1.e-14);

    // Calcuate solution with Energieeigentwert
    startVal[2] = E0;
    cout << E0 << endl;
    numerov(startVal);

    return 0;
}