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

def calcTotalEnergy(kinetic, potetial):
    if len(kinetic) is not len(potetial):
        print('Längen der Daten nicht gleich!')
        return
    totalEnergy = np.zeros(len(kinetic))
    index = 0
    while index < len(kinetic):
        totalEnergy[index] = kinetic[index] + potetial[index]
        index +=1
    return totalEnergy 


verletDataF = readData('Verlet-data-f.txt')
eulerData = readData('Euler-data.txt')
leapFrogDataX = readData('LF-data-x.txt', 2)
leapFrogDataV = readData('LF-data-v.txt', 2)
rungeKuttaData = readData('RK-data.txt')


#Testing energy calc 
kinetic = calcEnergy(eulerData, 1, 1)
potential = calcEnergy(eulerData, 2, 1)
totalEnergy = calcTotalEnergy(kinetic, potential)

fig, ax = plt.subplots()
ax.plot(eulerData[0], totalEnergy)
ax.plot(eulerData[0], eulerData[1])

"""
fig, axs = plt.subplots(2)
fig.suptitle('Verfahren im Vergleich')
axs[0].plot(rungeKuttaData[0], rungeKuttaData[1])
axs[0].plot(rungeKuttaData[0], rungeKuttaData[2])
axs[1].plot(eulerData[0], eulerData[1])
axs[1].plot(eulerData[0], eulerData[2])
"""
plt.show()
