import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

# uses TeX for rendering text. Time to execute script 3.3 seconds up from 0.03 seconds when disabled
mpl.rcParams['text.usetex'] = 'True'

# Functions of the analytical solution
def chi(r):
    return 1-(1+r/2)*np.exp(-r)

def phi(r):
    return 1/r-(1/r+1/2)*np.exp(-r)

# get the data from file 'data'
x,y,z=np.loadtxt('/home/jakob/git/cophy1/blatt4/data', delimiter=' ', unpack=True)

# first figure: plot for chi(x)
plt.figure(1)
plt.plot(x,y,'--',label='Unkorrigierte Lösung')
plt.plot(x,z,'--',label='Korrigierte Lösung')

r=np.arange(0,20,0.01)
plt.plot(r,chi(r), '--',label='Analytische Lösung')

plt.axis([0, 20, 0, 5])
plt.xlabel(r"Abstand $r$")
plt.ylabel(r"$4\pi\varepsilon_0\ \chi(r)$")
plt.legend()
plt.grid()
plt.savefig('/home/jakob/git/cophy1/blatt4/images/figure1.pdf')


# second figure: plots for phi(x)=chi(x)/x
plt.figure(2)

plt.plot(x,(y/x),'--',label='Unkorrigierte Lösung')
plt.plot(x,(z/x),'--',label='Korrigierte Lösung')
plt.plot(r,phi(r),'--',label='Analytische Lösung')

plt.axis([0, 20, 0, 1])
plt.xlabel(r"Abstand $r$")
plt.ylabel(r"$4\pi\varepsilon_0\ \varphi(r)$")
plt.legend()
plt.grid()
plt.savefig('/home/jakob/git/cophy1/blatt4/images/figure2.pdf')
