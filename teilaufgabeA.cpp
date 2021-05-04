#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Deklaration der Methoden:
void euler(const double[], string);
void rungeKutta(const double[], string);
void leapFrog(const double init[], string name);

int main()
{
    cout << "-----Start main-----" << endl;

    /*
    ---------MODIFY---------
    Ändern: Anfangswerte und/ oder Filenames
    sonst werden Standartwerte verwendet 
    */

    //Bedeutung der Werte nach Reihenfolge: Laufzeit, Schrittweite, Omega, Startwert x, Startwert y
    double init[5] = {30.0, 0.01, 1.0, 5.0, 0.0};

    //Name des Files in welches die Werte geschreiben werden
    string filenameEuler = "euler-data.txt";
    string dateinameRK = "RK-data.txt";
    string dateinameLF = "LF-data.txt";

    //Aufrufen der Funktionen
    euler(init, filenameEuler);
    rungeKutta(init, dateinameRK);
    leapFrog(init, dateinameLF);
    return 0;
}

void euler(const double init[], string name)
{
    cout << "Start euler. Writing in File: " << name << endl;

    // Öffne 'File' zu schreiben
    ofstream File(name);

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

void leapFrog(const double init[], string name)
{
    cout << "Start leapFrog. Writing in File: " << name << endl;

    // Öffne 'File' zu schreiben
    ofstream File(name);

    // leap Frog Verfahren
    double h = init[1], omega = init[2], x = init[3], v = init[4], xnew, vnew, temp;

    // Außnahme beim ersten Schritt - bestimmung von v_(n+1/2) durch euler (da v_(n-1/2) nicht existiert)
    temp = v - h * omega * omega * x;
    vnew = (v + temp) / 2.; // Linear interpoliert
    xnew = x + h * vnew;
    File << 0 << " " << xnew << " " << vnew << "\n";
    x = xnew;
    v = vnew;

    for (double t = h; t <= init[0]; t += h)
    {
        vnew = v - h * omega * omega * x;
        xnew = x + h * vnew;

        // In File schreiben
        File << t << " " << xnew << " " << vnew << "\n";
        x = xnew;
        v = vnew;
    }
    // 'File' wieder schließen
    File.close();
}