import matplotlib.pyplot as plt
import numpy as np

def countLines(filename):
    with open(filename) as f:
        i = 0
        for line in f:
            i += 1
            if line == "":
                break
        return i


def readData(filename, axis=3):
    data = np.zeros((axis, countLines(filename)))
    with open(filename) as f:
        index = 0
        for l in f:
            stringArray = l.split()
            for i in range(axis):
                data[i][index] = float(stringArray[i])
            index += 1
            if l == "":
                break
    return data

# Berechnen einer Energie nach der Form e = 0.5 * A * x**2
def calcEnergy(data, axis, A = 1):
    energyData = np.zeros(len(data[axis]))
    index = 0
    for val in data[axis]:
        energyData[index] = 0.5 * A * pow(val, 2)
        index += 1
    return energyData

def calcTotalEnergy(kinetic, potential):
    if len(kinetic) != len(potential):
        print('Längen der Daten nicht gleich!')
        return
    totalEnergy = np.zeros(len(kinetic))
    firstVal = kinetic[0] + potential[0]
    index = 0
    while index < len(kinetic):
        totalEnergy[index] = kinetic[index] + potential[index] - firstVal
        index +=1
    return totalEnergy

#berechne (x_(analytisch) - x_(numerisch))^2 -- also Fehler
def calcError(data, refdata):
    error = np.zeros(len(data))
    index = 0
    while index < len(data):
        error[index] = pow(data[index] - refdata[index], 2)
        index += 1
    return error


# Zum Debuggen (viellecht hat np eine analoge funktion)
def printFrist(data):
    index = 0
    while index < 30:
        print(data[index])
        index += 1

teilC = readData('Verlet-data-1.txt', 2)
teilC1 = readData('Verlet-data-2.txt', 2)
teilC2 = readData('Verlet-data-3.txt', 2)

plt.plot(teilC[0], teilC[1], label="callVerlet")
plt.plot(teilC1[0], teilC1[1], label="verletV2")
plt.plot(teilC2[0], teilC2[1], label="verletV3")

plt.legend()
plt.grid()
plt.show()

# Daten einlesen
"""
eulerData = readData('Euler-data.txt')
rungeKuttaData = readData('RungeKutta-data.txt')
leapFrogData = readData('LeapFrog-data.txt')
verletDataF = readData('Verlet-data-f.txt')
refData = readData('Reference-data.txt', 2)
"""

# Plot Error
"""
error = calcError(eulerData[1], refData[1])
errorRK = calcError(rungeKuttaData[1], refData[1])
errorLF = calcError(leapFrogData[1], refData[1])

plt.plot(eulerData[0], error, label='Euler')
plt.plot(eulerData[0], errorRK, label='Runge-Kutta')
plt.plot(eulerData[0], errorLF, label='Leap-Frog')

plt.title('Vergleich Fehler bei h=0.01')
plt.xlabel('Zeit t')
plt.ylabel('Fehler |(x_(numerisch)-x_(analytisch)|^2')

plt.legend()
"""
# Calc Energy
"""
kinetic = calcEnergy(eulerData, 1)
potential = calcEnergy(eulerData, 2)
totalEnergy = calcTotalEnergy(kinetic, potential)

kineticLF = calcEnergy(leapFrogData, 1)
potentialLF = calcEnergy(leapFrogData, 2)
totalEnergyLF = calcTotalEnergy(kineticLF, potentialLF)

kineticRK = calcEnergy(rungeKuttaData, 1)
potentialRK = calcEnergy(rungeKuttaData, 2)
totalEnergyRK = calcTotalEnergy(kineticRK, potentialRK)

plt.plot(leapFrogData[0], leapFrogData[1], label='Leap-Frog')
plt.plot(leapFrogData[0], refData[1], label='Analytisch')
plt.plot(leapFrogData[0], totalEnergyLF, label='E_ges - E_(0)')

plt.title('Leap-Frog bei h=0.01')
plt.xlabel('Zeit t')
plt.ylabel('Auslenkung x')

plt.grid()
plt.legend()
"""

#Plotting Energy
"""
fig, axs = plt.subplots(3)

fig.suptitle('Verfahren im Vergleich zu analytischer Lösung und Gesamtenergie (h=0.5)')

axs[0].plot(eulerData[0], refData[1])
axs[0].plot(eulerData[0], eulerData[1])
axs[0].plot(eulerData[0], totalEnergy)
axs[0].set_title('Euler-Verfahren')
axs[0].grid()

axs[1].plot(leapFrogData[0], refData[1])
axs[1].plot(leapFrogData[0], leapFrogData[1])
axs[1].plot(leapFrogData[0], totalEnergyLF)
axs[1].set_title('Leap-Frog-Verfahren')
axs[1].grid()

axs[2].plot(rungeKuttaData[0], refData[1])
axs[2].plot(rungeKuttaData[0], rungeKuttaData[1])
axs[2].plot(eulerData[0], totalEnergyRK)
axs[2].set_title('Runge-Kutta-Verfahren')
axs[2].grid()

plt.xlabel('Zeit t')
"""

# Teilaufgabe b
"""
verletV1 = readData('Verlet-data-1.txt')
verletV2 = readData('Verlet-data-2.txt')
verletV3 = readData('Verlet-data-3.txt')


# Plotting
fig, axs = plt.subplots(3)

fig.suptitle('Verlet Verfahren mit unterschiedlicher Dämpfung')

axs[0].plot(verletV1[0], verletV1[1])
axs[0].set_title('Schwingfall (d = 0.5)')
axs[0].grid()

axs[1].plot(verletV2[0], verletV2[1])
axs[1].set_title('Aperiodischer Grenzfall (d =2)')
axs[1].grid()

axs[2].plot(verletV3[0], verletV3[1])
axs[2].set_title('Kriechfall')
axs[2].grid()

plt.xlabel('Auslenkung x')

axs[0].set(ylabel='Geschwindigkeit v')
axs[1].set(ylabel='Geschwindigkeit v')
axs[2].set(ylabel='Geschwindigkeit v')


plt.show()
"""