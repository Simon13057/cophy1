# Hab die Plots per Hand gemacht indem ich ftsc.c und crank-nicolson.c für verschiedene
# Zeiten kompiliert hab. Nicht nachmachen

import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl

# uses TeX for rendering Text and Math
mpl.rcParams['text.usetex'] = 'True'


# plot the snapshots and save to file
fig,ax=plt.subplots()
ax.set_xlabel("x-Position")
ax.set_ylabel(r"$\varphi(x)$")
ax.set_xlim(.3,.7)
ax.set_ylim(0,1)
x,y0,y01,y05,y1=np.loadtxt('/home/jakob/git/cophy1/blatt5/diffusion2d.dat',unpack=True)
x2,cn=np.loadtxt('/home/jakob/git/cophy1/blatt5/crank-nicolson.dat',unpack=True)

ax.plot(x,y1,label='FTCS-Schema')
ax.plot(x2,cn,label='Crank-Nicolson')

ax.grid()
ax.legend()
# plt.show()
plt.savefig('ftcs-instable-100.png',dpi=600)