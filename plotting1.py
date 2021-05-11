import matplotlib.pyplot as plt
import numpy as np

# No comments

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
        energyData[index] = 0.5 * A * val**2
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

# Zum Debuggen (viellecht hat np eine analoge funktion)
def printFrist(data):
    index = 0
    while index < 30:
        print(data[index])
        index += 1

eulerData = readData('Euler-data.txt')
rungeKuttaData = readData('RungeKutta-data.txt')
leapFrogData = readData('LeapFrog-data.txt')
verletDataF = readData('Verlet-data-f.txt')

refData = readData('Reference-data.txt', 2)

#Testing energy calc 
kinetic = calcEnergy(eulerData, 1)
potential = calcEnergy(eulerData, 2)
totalEnergy = calcTotalEnergy(kinetic, potential)

kineticLF = calcEnergy(leapFrogData, 1)
potentialLF = calcEnergy(leapFrogData, 2)
totalEnergyLF = calcTotalEnergy(kineticLF, potentialLF)

kineticRK = calcEnergy(rungeKuttaData, 1)
potentialRK = calcEnergy(rungeKuttaData, 2)
totalEnergyRK = calcTotalEnergy(kineticRK, potentialRK)


fig, axs = plt.subplots(3)

fig.suptitle('Verfahren im Vergleich zu analytischer Lösung und Gesamtenergie (h=0.0001)')
#fig.supxlabel('Zeit t')
#fig.supylabel('Auslenkung x')

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

"""
ax.grid()
ax1.set_title('damped')
ax1.set_xlabel('time (s)')
ax1.set_ylabel('amplitude')
fig.supxlabel('Year')
fig.supylabel('Percent Degrees Awarded To Women')

fig, axs = plt.subplots(2)
fig.suptitle('Verfahren im Vergleich')
axs[0].plot(rungeKuttaData[0], rungeKuttaData[1])
axs[0].plot(rungeKuttaData[0], rungeKuttaData[2])
axs[1].plot(eulerData[0], eulerData[1])
axs[1].plot(eulerData[0], eulerData[2])
"""

plt.show()
