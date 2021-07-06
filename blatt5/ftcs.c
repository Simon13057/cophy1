#include <stdio.h>
#include <math.h>

#define SAMPLES 500
#define DX 0.002
#define TIME_STEPS 1000
#define DT 0.001
#define D 0.001
#define ALPHA (D*DT/DX/DX) // ALPHA should be >1/2, otherwise the method is not stable
#define X_0 0.5
#define SIGMA 0.02

double gaussian(double x);

int main()
{
    printf("alpha is %g\n",ALPHA); // check if you screwed up

    /* Initialize the starting values on a 1D plane */
    double data[SAMPLES][TIME_STEPS];
    for(int i = 0; i < SAMPLES; i++)
    {
        data[i][0] = gaussian(i*DX);
    }

    /* Iterate over the array for every time step */
    for (int i = 0; i < SAMPLES; i++)
    {
        if(i==0)
        {
            for (int n = 0; n < TIME_STEPS-1; n++)
            {
                data[i][n+1] = data[i][n] + ALPHA*(data[i+1][n]-2*data[i][n]+data[i][n]);
            }
        }
        else if (i==SAMPLES-1)
        {
            for (int n = 0; n < TIME_STEPS-1; n++)
            {
                data[i][n+1] = data[i][n] + ALPHA*(data[i][n]-2*data[i][n]+data[i-1][n]);
            }
        }
        else
        {
            for (int n = 0; n < TIME_STEPS-1; n++)
            {
                data[i][n+1] = data[i][n] + ALPHA*(data[i+1][n]-2*data[i][n]+data[i-1][n]);
            }
        }
        
    }

    /* Write the resulting matrix to a file. Can be plotted with gnuplot> splot "diffusion3d.dat" */
    FILE *f = fopen("diffusion3d.dat","w");
    for (int n = 0; n < TIME_STEPS; n++)
    {
        for (int i = 0; i < SAMPLES; i++)
        {
            fprintf(f, "%g %g %g\n", n*DT, i*DX, data[i][n]);
        }
        fprintf(f,"\n");
    }
    fclose(f);

    /* Write snapshots at several timestamps to a file */
    FILE *f2 = fopen("diffusion2d.dat","w");
    fprintf(f2,"# x t=0 t=0.1 t=0.5 t=1");
    
    for (int i = 0; i < SAMPLES; i++)
    {
        fprintf(f2,"%g %g %g %g %g\n",i*DX,data[i][0],data[i][100],data[i][500],data[i][1000]);
    }
    fclose(f2);

    return 0;
}

double gaussian(double x)
{
    return exp(-(x-X_0)*(x-X_0)/2./SIGMA/SIGMA);
}