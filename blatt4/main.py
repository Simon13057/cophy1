"""
Plotting shooting method results for the schroedinger equation
"""

from Files import Solution
import matplotlib.pyplot as plt
import numpy as np

import matplotlib as mpl
mpl.rcParams['mathtext.fontset'] = 'cm'
mpl.rcParams['mathtext.rm'] = 'serif'

dataE1 = Solution("e1.dat")
dataE2 = Solution("e2.dat")
dataE3 = Solution("e3.dat")
dataE4 = Solution("e4.dat")
dataE5 = Solution("e5.dat")

plt.plot(dataE1.x, dataE1.y, label="$E_1 + \psi_1(x)$")
plt.plot(dataE1.x, dataE1.z, linewidth=1, linestyle=":", color="y")
plt.plot(dataE2.x, dataE2.y, label="$E_2 + \psi_2(x)$")
plt.plot(dataE1.x, dataE2.z, linewidth=1, linestyle=":", color="y")
plt.plot(dataE3.x, dataE3.y, label="$E_3 + \psi_3(x)$")
plt.plot(dataE1.x, dataE3.z, linewidth=1, linestyle=":", color="y")
plt.plot(dataE4.x, dataE4.y, label="$E_4 + \psi_4(x)$")
plt.plot(dataE1.x, dataE4.z, linewidth=1, linestyle=":", color="y")
plt.plot(dataE5.x, dataE5.y, label="$E_5 + \psi_5(x)$")
plt.plot(dataE1.x, dataE5.z, linewidth=1, linestyle=":", color="y")

plt.plot(range(10), label="Potential V(x)",linewidth=1, linestyle="--", color="g")

plt.ylabel("Wellenfunktion $\psi_n(x)$ von verschiedenen Energieeigenwerten $E_n$")
plt.xlabel("x")

plt.legend()
plt.grid()
plt.show()