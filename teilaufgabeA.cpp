#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Deklaration der Methoden:
void euler(const double[], string);
void rungeKutta(const double[], string);
void leapFrog(const double[], string, string);
void verlet(const double[], string);

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
    double initV[6] = {30.0, 0.01, 1.0, 5.0, 0.0, 0.1};

    //Name des Files in welches die Werte geschreiben werden
    string filenameEuler = "Euler-data.txt";
    string dateinameRK = "RK-data.txt";
    string dateinameLFx = "LF-data-x.txt";
    string dateinameLFv = "LF-data-v.txt";
    string dateinameV = "Verlet-data.txt";

    //Aufrufen der Funktionen
    euler(init, filenameEuler);
    rungeKutta(init, dateinameRK);
    leapFrog(init, dateinameLFx, dateinameLFv);
    verlet(initV, dateinameV);
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

void rungeKutta(const double init[], std::string filename)
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
        k1x = h * v;
        k1v = -omega * omega * h * x;

        k2x = h * (v + k1v / 2.);
        k2v = -h * omega * omega * (x + k1x / 2.);

        xnew = x + k2x;
        vnew = v + k2v;

        //write in File
        File << t << " " << xnew << " " << vnew << "\n";

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