#include "solve.h"

using namespace std;

LeapFrog::LeapFrog()
{
    this->runtime = 30.0;
    this->h = 0.01;
}

LeapFrog::LeapFrog(double runtime, double h)
{
    this->runtime = runtime;
    this->h = h;
}

double *f(double vals[5])
{
    static double a[2] = {0.0, 0.0};

    double x1 = vals[0];
    double x2 = vals[1];
    double y1 = vals[2];
    double y2 = vals[3];
    double m = vals[4];

    double temp = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);

    a[0] = m * (x2 - x1) * 1. / pow(temp, (3. / 2.));
    a[1] = m * (y2 - y1) * 1. / pow(temp, (3. / 2.));

    return a;
}

void LeapFrog::leapfrog_2obj(Object first, Object &second)
{
    cout << "First Object: " << first.print_vals() << endl;
    cout << "Second Object: " << second.print_vals() << endl;

    double minDistance = first.get_radius() + second.get_radius();

    ofstream file1("First_Obj.dat");
    ofstream file2("Second_Obj.dat");
    double t = 0;
    while (t <= this->runtime)
    {
        double temp1[5] = {first.x, second.x, first.y, second.y, second.get_m()};
        double temp2[5] = {second.x, first.x, second.y, first.y, first.get_m()};

        double *a1 = f(temp1);
        double ax1 = *a1;
        double ay1 = *(a1 + 1);

        double *a2 = f(temp2);
        double ax2 = *a2;
        double ay2 = *(a2 + 1);

        double tempDistance = sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
        if (tempDistance <= minDistance)
        {
            cout << "the objects CRASHED" << endl;
            second.vx = first.vx;
            second.vy = first.vy;
            t = this->runtime;
        }

        if (file1.is_open())
        {
            file1 << t << ";" << first.print_vals() << first.get_vges() << ";" << first.get_kinE() << endl;
        }

        if (file2.is_open())
        {
            file2 << t << ";" << second.print_vals() << second.get_vges() << ";" << second.get_kinE() << endl;
        }

        double vxph1 = first.vx + this->h * ax1;
        double vyph1 = first.vy + this->h * ay1;

        double xp1 = first.x + this->h * vxph1;
        double yp1 = first.y + this->h * vyph1;

        first.x = xp1;
        first.y = yp1;
        first.vx = vxph1;
        first.vy = vyph1;

        double vxph2 = second.vx + this->h * ax2;
        double vyph2 = second.vy + this->h * ay2;

        double xp2 = second.x + this->h * vxph2;
        double yp2 = second.y + this->h * vyph2;

        second.x = xp2;
        second.y = yp2;
        second.vx = vxph2;
        second.vy = vyph2;

        t += this->h;
    }
    file1.close();
    file2.close();
}

double LeapFrog::max_vges(Object first, double x_start, double y_start, double vges_start, double mass, double radius)
{
    double phi_max = 0;
    double v_max = 0;

    ofstream file("shooting_data.csv");

    double phi = M_PI * 4. / 3.;
    while (phi < M_PI * 5. / 3.)
    {
        double vx = sin(phi) * vges_start;
        double vy = cos(phi) * vges_start;

        Object second(x_start, y_start, vx, vy, mass, radius);
        this->leapfrog_2obj(first, second);

        double v_end = second.get_vges();
        if (v_end >= v_max)
        {
            phi_max = phi;
            v_max = v_end;
        }
        if (file.is_open())
        {
            file << phi << ";" << v_end << endl;
        }
        phi += M_PI / 180 * 0.5;
    }
    file.close();
    return phi_max;
}
