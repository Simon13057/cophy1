#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

//Deklaration der Methoden:
void euler(const double[], string);
void rungeKutta(const double[], string);
void leapFrog(const double[], string, string);
void leapFrog(const double [], string); // Data in ein File statt 2 Files schreiben (mit linearer interpolation)
void verlet(const double[], string); // Mit Dämpfung
void verlet(const double[], const double[], string); // Mit externer Kraft und Dämpfung
void referenceData(const double [], string);
double verletMax(const double [], const double []);
void callVerlet(string, double const [], double []);

int main()
{
    cout << "-----Start main-----" << endl;

    /*
    Ändern: Anfangswerte und/ oder Filenames
    sonst werden Standartwerte verwendet 
    */

    // Bedeutung der Werte nach Reihenfolge: Laufzeit, Schrittweite, Omega, Startwert x, Startwert v
    double init[5] = {30.0, 0.01, 1.0, 5.0, 0.0};
    // Werte mit Dämpfung (letzter Eintrag ist Dämpfungskoeffizient)
    double initV[6] = {160.0, 0.1, 1., 2.0, 2.0, 1};
    double initV2[6] = {30.0, 0.1, 3., 5.0, 0.0, 3};
    double initV3[6] = {30.0, 0.1, 10., 5.0, 0.0, 0.5};
    // Mit anregender kraft. Werte nach Reihenfolge: Amplitude A, Frequenz F, Phasenversch P
    // Ergibt Funktion: a(t) = A * sin(F*t+P)
    double aKraft1[3] = {5.0, 0.0, 0.0};
    double aKraft2[3] = {5.0, 0.15, 0.0};

    /*
    //Name des Files in welches die Werte geschreiben werden
    string filenameEuler = "Euler-data.txt";
    string dateinameRK = "RungeKutta-data.txt";
    //string dateinameLFx = "LF-data-x.txt";
    //string dateinameLFv = "LF-data-v.txt";
    string dateinameLF = "LeapFrog-data.txt";
    string dateinameRef = "Reference-data.txt";

    //Aufrufen der Funktionen
    referenceData(init, dateinameRef);
    euler(init, filenameEuler);
    rungeKutta(init, dateinameRK);
    //leapFrog(init, dateinameLFx, dateinameLFv);
    leapFrog(init, dateinameLF);
    */

    string dateinameV1 = "Verlet-data-1.txt";
    string dateinameV2 = "Verlet-data-2.txt";
    string dateinameV3 = "Verlet-data-3.txt";
    //ohne antreibende Kraft, mit Dämpfung
    //verlet(initV, aKraft, dateinameV1);
    //verlet(initV2, aKraft,dateinameV2);
    //verlet(initV3, aKraft, dateinameV3);             
    //string dateinameVwF = "Verlet-data-f.txt";
    //verlet(initV, aKraft1, dateinameV2);
    //verlet(initV, aKraft2, dateinameV3);
    callVerlet(dateinameV1, initV, aKraft1);    //mit antreibender Kraft
    callVerlet(dateinameV2, initV2, aKraft1); 
    callVerlet(dateinameV3, initV3, aKraft1); 
    return 0;
}

void euler(const double init[], string name)
{
    cout << "Start euler. Writing in File: " << name << endl;

    // Öffne 'File' zu schreiben
    ofstream File(name);
    if (File.fail())
    {
        cout << "Error with File in Euler() Func" << endl;
        return;
    }
    // Explizites Euerverfahren
    double h = init[1], omega = init[2], x = init[3], y = init[4], xp, yp;
    for (double t = 0; t <= init[0]; t += h)
    {
        xp = x + h * y;
        yp = y - h * omega * omega * x;

        // In File schreiben
        File << t << " " << xp << " " << yp << "\n";

        x = xp;
        y = yp;
    }
    // 'File' wieder schließen
    File.close();
}

void referenceData(const double init[], string name)
{
    cout << "Berechne Analytische Lösung. Writing in File: " << name << endl;

    // Öffne 'File' zu schreiben
    ofstream File(name);
    if (File.fail())
    {
        cout << "Error with File in referenceData() Func" << endl;
        return;
    }
    // Explizites Euerverfahren
    double h = init[1], omega = init[2], x0 = init[3], y0 = init[4], k1, k2,x;

    for (double t = 0; t <= init[0]; t += h)
    {
        k1 = y0 * sin(omega*t)/omega;
        k2 = x0*cos(omega*t);
        x = k1 + k2;
        // In File schreiben
        File << t << " " << x << "\n";
    }
    // 'File' wieder schließen
    File.close();
}

void rungeKutta(const double init[], string filename)
{
    cout << "Start rungeKutta. Writing in File: " << filename << endl;

    // Öffne 'File' zu schreiben
    ofstream File(filename);
    if (File.fail())
    {
        cout << "Error with File in rungeKutta() Func" << endl;
        return;
    }

    // Runge Kutta Verfahren 2 Ordnung
    double h = init[1], omega = init[2], x = init[3], v = init[4];
    double k1x, k1v, k2x, k2v, xnew, vnew;
    for (double t = 0; t <= init[0]; t += h)
    {
        //write in File
        File << t << " " << x << " " << v << "\n";

        k1x = h * v;
        k1v = -omega * omega * h * x;

        k2x = h * (v + k1v / 2.);
        k2v = -h * omega * omega * (x + k1x / 2.);

        xnew = x + k2x;
        vnew = v + k2v;

        x = xnew;
        v = vnew;
    }
    //File schließen
    File.close();
}

void leapFrog(const double init[], string filenameX, string filenameV)
{
    // Erstelle zwei getrennte Dateien für x und v Werte bzgl. der Zeit
    cout << "Start leapFrog." << endl;
    cout << "Write time - Position in:" << filenameX << endl;
    cout << "Write time - Speed in:" << filenameV << endl;

    // Öffne 'File' zu schreiben
    ofstream FileX(filenameX);
    ofstream FileV(filenameV);
    if (FileX.fail() || FileV.fail())
    {
        cout << "Error with File in leapFrog() Func" << endl;
        return;
    }

    // leap Frog Verfahren
    double h = init[1], omega = init[2], x = init[3], v = init[4], xnew, vnew, temp;

    // Außnahme beim ersten Schritt - bestimmung von v_(n+1/2) durch euler (da v_(n-1/2) nicht existiert)
    temp = v - h * omega * omega * x;
    vnew = (v + temp) / 2.; // Linear interpoliert
    FileV << 0 << " " << v << "\n";
    FileV << h / 2. << " " << vnew << "\n";
    FileX << 0 << " " << x << "\n";
    v = vnew;

    for (double t = h; t <= init[0]; t += h)
    {
        xnew = x + h * v;
        vnew = v - h * omega * omega * x;

        // In entsprechende File schreiben
        FileX << t << " " << xnew << "\n";
        FileV << t + h / 2. << " " << vnew << "\n";

        x = xnew;
        v = vnew;
    }
    // 'File' wieder schließen
    FileX.close();
    FileV.close();
}

void leapFrog(const double init[], string filename)
{
    // Erstelle Dateien
    cout << "Start leapFrog." << endl;
    cout << "Write in:" << filename << endl;

    // Öffne 'File' zu schreiben
    ofstream File(filename);
    if (File.fail() )
    {
        cout << "Error with File in leapFrog() Func" << endl;
        return;
    }

    // leap Frog Verfahren
    double h = init[1], omega = init[2], x = init[3], v = init[4], xnew, vnew, temp;

    // Außnahme beim ersten Schritt - bestimmung von v_(n+1/2) durch euler (da v_(n-1/2) nicht existiert)
    temp = v - h * omega * omega * x;
    vnew = (v + temp) / 2.; // Linear interpoliert
    File << 0 << " " << x << " " << v << "\n";
    v = vnew;

    for (double t = h; t <= init[0]; t += h)
    {
        xnew = x + h * v;
        vnew = v - h * omega * omega * xnew;

        temp = (v + vnew) / 2.; // linear interpoliert um v_(n+1) zu erhalten statt v_(n+3/2)

        // In entsprechende File schreiben
        File << t << " " << xnew << " " << temp << "\n";

        x = xnew;
        v = vnew;
    }
    // 'File' wieder schließen
    File.close();
}

void verlet(const double init[], string filename)
{
    cout << "Start verlet. Writing in File: " << filename << endl;

    // Öffne 'File' zu schreiben
    ofstream File(filename);
    if (File.fail())
    {
        cout << "Error with File in verlet() Func" << endl;
        return;
    }

    // Verlet Verfahren
    double h = init[1], omega = init[2], xp = init[3], vp = init[4], d = init[5];
    double k1, k2, k3, xn, x, v; // xn = x_(n+1), x = x_(n), xp = x_(n-1) -- entsprechend v -- k sind zwischenergebnisse
    // Bestimme x durch Anfangsgeschw mittels euler
    x = xp + h * vp;
    File << 0 << " " << xp << " " << vp << "\n";
    for (double t = h; t <= init[0]; t += h)
    {
        k1 = 2.0 * x * (2.0 - h * h * omega * omega);
        k2 = xp * (d * h - 2.0);
        k3 = 1.0 / (2.0 + d * h);

        xn = (k1 + k2) * k3;
        v = (xn - xp) / (2.0 * h);

        // In File schreiben
        File << t << " " << x << " " << v << "\n";

        xp = x;
        x = xn;
    }
    //File schließen
    File.close();
}

void verlet(const double init[], const double initForce[], string filename)
{
    cout << "Start verlet with external Force. Writing in File: " << filename << endl;

    // Öffne 'File' zu schreiben
    ofstream File(filename);
    if (File.fail())
    {
        cout << "Error with File in verlet() Func" << endl;
        return;
    }

    // Verlet Verfahren
    const double h = init[1], omega = init[2], A = initForce[0], F = initForce[1], P = initForce[2];
    double xp = init[3], vp = init[4], d = init[5];
    double k1, k2, k3, k4, xn, x, v; // xn = x_(n+1), x = x_(n), xp = x_(n-1) -- entsprechend v -- k sind zwischenergebnisse

    // Bestimme x durch Anfangsgeschw mittels Euler
    x = xp + h * vp;
    File << 0 << " " << xp << " " << vp << "\n";
    for (double t = h; t <= init[0]; t += h)
    {
        k1 = 2.0 * x * (2.0 - h * h * omega * omega);
        k2 = xp * (d * h - 2.0);
        k3 = 1.0 / (2.0 + d * h);
        k4 = 2 * h * h * A * sin(F * t + P);

        xn = (k1 + k2 + k4) * k3;
        v = (xn - xp) / (2.0 * h);

        // In File schreiben
        File << t << " " << x << " " << v << "\n";

        xp = x;
        x = xn;
    }
    //File schließen
    File.close();
}


double verletMax(const double init[], const double initForce[])
{
    // Verlet Verfahren
    const double h = init[1], omega = init[2], A = initForce[0], F = initForce[1], P = initForce[2];
    double xp = init[3], vp = init[4], d = init[5];
    double k1, k2, k3, k4, xn, x, v; // xn = x_(n+1), x = x_(n), xp = x_(n-1) -- entsprechend v -- k sind zwischenergebnisse

    // Maximale Amplitude
    double max = 0;

    // Bestimme x durch Anfangsgeschw mittels Euler
    x = xp + h * vp;
    
    for (double t = h; t <= init[0]; t += h)
    {
        k1 = 2.0 * x * (2.0 - h * h * omega * omega);
        k2 = xp * (d * h - 2.0);
        k3 = 1.0 / (2.0 + d * h);
        k4 = 2 * h * h * A * sin(F * t + P);

        xn = (k1 + k2 + k4) * k3;
        v = (xn - xp) / (2.0 * h);

        // ab t = 5 suche nach Max (nach einschwingvorgang)
        if(t >= 10 && xn >= max){
            max = xn;
        }

        xp = x;
        x = xn;
    }
    //File schließen
    return max;
}

// Achtung! Annahme: omega = 1
void callVerlet(string filename, double const init[], double aKraft[])
{
    // Initalise callVerlet
    double maxOmega = 3.0;
    double h = 0.01;
    double max = 0.0;

    ofstream File(filename);
    if(File.fail()){
        cout << "Fehler mit File in callVerlet Fuc" << endl;
    }
    
    for(double omega = h; omega <= maxOmega; omega += h){
        
        aKraft[1] = omega;
        max = verletMax(init, aKraft);

        File << omega <<  " " << max/init[3] << "\n";
    }

    File.close();
}