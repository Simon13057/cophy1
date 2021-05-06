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


verletDataF = readData('Verlet-data-f.txt')
eulerData = readData('euler-data.txt')
leapFrogDataX = readData('LF-data-x.txt', 2)
leapFrogDataV = readData('LF-data-v.txt', 2)
rungeKuttaData = readData('RK-data.txt')

fig, axs = plt.subplots(2)
fig.suptitle('Verfahren im Vergleich')
axs[0].plot(rungeKuttaData[0], rungeKuttaData[1])
axs[0].plot(rungeKuttaData[0], rungeKuttaData[2])
axs[1].plot(eulerData[0], eulerData[1])
axs[1].plot(eulerData[0], eulerData[2])

plt.show()
