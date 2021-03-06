import matplotlib.pyplot as plt
import numpy as np
import math

def verletMax(init, force):
    h = init[1] #Bedeutung siehe unten
    omega = init[2]
    xp = init[3]
    vp = init[4]
    d = init[5]
    a = force[0]
    f = force[1]

    max = 0
    end = init[0]/2. #Ende Einschwingvorgang
    x = xp + h * vp

    t = h
    while t <= init[0]:
        k1 = 2.0 * x * (2.0 - h * h * omega * omega)
        k2 = xp * (d * h - 2.0)
        k3 = 1.0 / (2.0 + d * h)
        k4 = 2 * h * h * a * math.sin(f * t)

        xn = (k1 + k2 + k4) * k3
    
        if t >= end and xn >= max:
            max = xn

        xp = x
        x = xn

        t += h

    return max

def callVerletMax(init, force):
    maxOmega  = 3.
    h = 0.01

    res = np.zeros((2, (int(maxOmega/h))))

    omega = 0.01
    index = 0
    while omega <= maxOmega:
        res[0][index] = omega
        force[1] = omega
        init[0] = 150/(omega*init[5])  #Anpassen -- entspricht Laufzeit
        max = verletMax(init, force)
        res[1][index] = max
        omega += h
        index += 1

    return res

def verlet(init, force):
    h = init[1]
    omega = init[2]
    xp = init[3]
    vp = init[4]
    d = init[5]
    a = force[0]
    f = force[1]

    res = np.zeros((2, (int(init[0]/h)+1)))
    
    x = xp + h * vp
    t = 0
    index = 0
    while t <= init[0]:
        k1 = 2.0 * x * (2.0 - h * h * omega * omega)
        k2 = xp * (d * h - 2.0)
        k3 = 1.0 / (2.0 + d * h)
        k4 = 2 * h * h * a * math.sin(f * t)

        xn = (k1 + k2 + k4) * k3

        res[0][index] = t
        res[1][index] = x

        xp = x
        x = xn

        t += h
        index += 1

    return res

def plotting(toPlot, label):

    plt.plot(toPlot[0], toPlot[1], label=label)
    
    plt.xlabel('omega_A/omega_0')
    plt.ylabel('x_max/x_0')
    plt.grid()
    plt.legend()

    plt.show()

def teilD(init, force, filename): #für 3d plot 
    d = 0.5 
    h = 0.1
    with open(filename, "w") as f:
        while d <= 1.5:
            init[5] = d
            res = callVerletMax(init, force)
            index = 0
            while index < len(res[0]):
                f.write(str(d) + " " + str(res[0][index]) + " " + str(res[1][index]) + "\n")
                index += 1
            f.write("\n")
            d += h

# Main --- PLOTTING

#Bedeutung der Werte nach Reihenfolge: Laufzeit, Schrittweite, Omega, Startwert x, Startwert v, Dämpfung d
#Mit anregender kraft. Werte nach Reihenfolge: Amplitude A, Frequenz F

initV1 = np.array([100,0.01,1,1,0,1])
initV2 = np.array([100,0.01,1,1,0,3])

init = np.array([100,0.01,1,1,0,2])
force = np.array([1, 0.5])

#teilD(init, force, "teilD.txt")
#init[0] = 65/force[1]
#res = verlet(initV2, force)
#print(verletMax(init, force))

#res = callVerletMax(init, force)
#plotting(res, 'Testing')

res = callVerletMax(init, force)
res1 = callVerletMax(initV1, force)
res2 = callVerletMax(initV2, force)


plt.plot(res[0], res[1], label='d=3')
plt.plot(res1[0], res1[1], label='d=1')
plt.plot(res2[0], res2[1], label='d=3')


plt.title('Resonanzkurven bei d >= 1')
plt.xlabel('omega_A/omega_0')
plt.ylabel('x_max/x_0')
plt.grid()
plt.legend()

plt.show()