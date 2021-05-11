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
def calcEnergy(data, axis, A):
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
    index = 0
    while index < len(kinetic):
        totalEnergy[index] = kinetic[index] + potential[index] - 12.5
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

#Testing energy calc 
kinetic = calcEnergy(eulerData, 1, 1)
potential = calcEnergy(eulerData, 2, 1)
totalEnergy = calcTotalEnergy(kinetic, potential)

fig, axs = plt.subplots(2)
axs[0].plot(eulerData[0], totalEnergy)
axs[0].plot(eulerData[0], eulerData[1])
axs[1].plot(leapFrogData[0], leapFrogData[1])
axs[1].plot(leapFrogData[0], leapFrogData[2])

"""
fig, axs = plt.subplots(2)
fig.suptitle('Verfahren im Vergleich')
axs[0].plot(rungeKuttaData[0], rungeKuttaData[1])
axs[0].plot(rungeKuttaData[0], rungeKuttaData[2])
axs[1].plot(eulerData[0], eulerData[1])
axs[1].plot(eulerData[0], eulerData[2])
"""

plt.show()

