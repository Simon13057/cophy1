import matplotlib.pyplot as plt
import numpy as np
import matplotlib as mpl

# uses TeX for rendering Text and Math
mpl.rcParams['text.usetex'] = 'True'

# input the colormap data on a 2D array and transpose it
x=np.arange(0,1,0.001)
y=np.arange(0,1,0.002)
Z=np.loadtxt('/home/jakob/git/cophy1/blatt5/colormap.dat')
Z=np.transpose(Z)

# plot the colormap and save to file
fig,ax=plt.subplots()
ax.set_xlabel("Zeit $t$")
ax.set_ylabel("x-Position")
ax.set_xlim(0,1)
ax.set_ylim(0.35,0.65)
colormap=ax.pcolormesh(x,y,Z,cmap='viridis')
fig.colorbar(colormap,ax=ax)
plt.savefig('colormap.png',dpi=600)

# plot the snapshots and save to file
fig2,ax2,=plt.subplots()
ax2.set_xlabel("x-Position")
ax2.set_ylabel(r"$\varphi(x)$")
ax2.set_xlim(.3,.7)
ax2.set_ylim(0,1)
x_2d,y0,y01,y05,y1=np.loadtxt('/home/jakob/git/cophy1/blatt5/diffusion2d.dat',unpack=True)

ax2.plot(x_2d,y0,label='$t=0$')
ax2.plot(x_2d,y01,label='$t=0.1$')
ax2.plot(x_2d,y05,label='$t=0.5$')
ax2.plot(x_2d,y1,label='$t=1$')

ax2.legend()
plt.savefig('ftcs_snapshots.png',dpi=600)