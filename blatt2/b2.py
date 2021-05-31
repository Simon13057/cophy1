import matplotlib.pyplot as plt
import numpy as np
import math

"""
Löst DGL der Magneten nach Verlet-Verfahren
Rückgabe: [Zeitpunkt, x-Koordinate, y-Koordinate]
"""


def verletMagnets(init, withMagnets):
    xp = init[0]
    yp = init[1]
    h = init[2]

    time = h
    data = np.zeros((3, 1))

    # Bestimme x,y mittels Euler
    # Wichtig: Annahme keine Anfangsgeschwindigkeit
    a = func(xp, yp, 0, 0, withMagnets)
    vx = h*a[0]
    vy = h*a[1]
    x = xp + vx * h
    y = yp + vy * h

    diffE = 1
    ep = a[2]

    # Speicher Initalwerte
    data[0][0] = 0
    data[1][0] = xp
    data[2][0] = yp

    # Solange sich die Energie merklich ändert Läuft die Schleife (anstatt fixe Laufzeit)
    while diffE >= 1*pow(10, -7):
        # Speichere Werte
        data = np.append(data, [[time], [x], [y]], axis=1)

        # Berechne Aktuelle Geschwindigkeit
        vx = (x - xp)/h
        vy = (y - yp)/h

        # Berechne neue Werte
        a = func(x, y, vx, vy, withMagnets)
        xn = 2*x + pow(h, 2)*a[0] - xp
        yn = 2*y + pow(h, 2)*a[1] - yp

        # Aktualisere Werte
        xp = x
        yp = y
        x = xn
        y = yn
        time += h
        e = a[2]
        diffE = abs(e - ep)
        ep = e

    return data


"""
Berechnet die Funktion nach umstellen der DGL: a(t) = f(x,y,v)
"""


def func(x, y, vx, vy, withMagnets):
    # Postion der Magneten sodass der Ursprung im Gleichgewicht ist
    x1 = 0
    y1 = 1/3
    x2 = -math.sqrt(3)/6
    y2 = -1/6
    x3 = math.sqrt(3)/6
    y3 = -1/6

    # z Koordinate des Balls
    z = 0.25

    # Sonstige Variablen
    mass = 1
    gamma = 0.5
    d = 0.2

    # Rechnung
    if withMagnets:
        k1 = pow(pow((x-x1), 2)+pow(y-y1, 2)+pow(z, 2), -1.5)
        k1x = -(x - x1) * k1
        k1y = -(y - y1) * k1
        k2 = pow(pow((x-x2), 2)+pow(y-y2, 2)+pow(z, 2), -1.5)
        k2x = -(x - x2) * k2
        k2y = -(y - y2) * k2
        k3 = pow(pow((x-x3), 2)+pow(y-y3, 2)+pow(z, 2), -1.5)
        k3x = -(x - x3) * k3
        k3y = -(y - y3) * k3

        ax = pow(mass, -1)*(k1x+k2x+k3x-d*vx-gamma*x)
        ay = pow(mass, -1)*(k1y+k2y+k3y-d*vy-gamma*y)

    else:
        ax = pow(mass, -1)*(-d*vx-gamma*x)
        ay = pow(mass, -1)*(-d*vy-gamma*y)

    # Berechnung Gesamtenergie
    totalEnergy = 0.5*mass*(pow(vx, 2) + pow(vy, 2)) + \
        0.5 * gamma * (pow(x, 2) + pow(y, 2))

    a = list((ax, ay, totalEnergy))

    return a


"""
Generiert Data für plt.pColor Funktion
"""


def calcColorData(initStart, withMagnets):
    h = 0.1
    x = -1
    y = -1
    data2Color = np.zeros((int(2/h) + 1, int(2/h) + 1))
    dataX = np.zeros((int(2/h) + 1, int(2/h) + 1))
    dataY = np.zeros((int(2/h) + 1, int(2/h) + 1))
    indexX = 0
    indexY = int(2/h)
    while abs(x) <= 1:
        while abs(y) <= 1:
            data = verletMagnets([x, y, initStart[2]], withMagnets)
            finalIndex = len(data[0]) - 1
            z = calcClosesetMagnet(data[1][finalIndex], data[2][finalIndex])
            data2Color[indexY][indexX] = z
            dataX[indexY][indexX] = x
            dataY[indexY][indexX] = y
            y += h
            indexY -= 1
        x += h
        y = -1
        indexX += 1
        indexY = int(2/h)
    return [data2Color, dataX, dataY]


"""
Berechnet nähsten Magnet anhand gegebener Koordinaten 
"""


def calcClosesetMagnet(x, y):
    # Postion der Magneten sodass der Ursprung im Gleichgewicht ist
    x1 = 0
    y1 = 1/3
    x2 = -math.sqrt(3)/6
    y2 = -1/6
    x3 = math.sqrt(3)/6
    y3 = -1/6

    # Berechnung Abstände
    d2First = pow(x-x1, 2) + pow(y-y1, 2)
    d2Second = pow(x-x2, 2) + pow(y-y2, 2)
    d2Third = pow(x-x3, 2) + pow(y-y3, 2)

    z = 0
    if d2First < d2Second and d2First < d2Third:
        z = 1
    elif d2Second < d2First and d2Second < d2Third:
        z = 2
    elif d2Third < d2Second and d2Third < d2First:
        z = 3

    return z


# Initalwerte
x = -0.3
y = 0.25
h = 0.1
initStart = list((x, y, h))
withMagnets = True

data = calcColorData(initStart, withMagnets)

# Plotting
fig, ax0 = plt.subplots()
ax0.pcolor(data[1], data[2], data[0], shading='auto')
plt.xlabel("x-Koordinate")
plt.ylabel("y-Koordinate")
plt.show()
