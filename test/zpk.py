# Graph zeros and poles of system.
# Also plots unit circle
import numpy as np
import scipy.signal as sig
import matplotlib.pyplot as plt

def plot(z, p, k):
  # Plot the zeros
  x = list((c.real for c in z))
  y = list((c.imag for c in z))
  plt.plot(x, y, 'o') # FIXME: un-fill the circle
  # Plot the poles
  x = list((c.real for c in p))
  y = list((c.imag for c in p))
  plt.plot(x, y, 'x')
  # Plot the unit circle
  circle = plt.Circle((0, 0), 1, color='b', fill=False)
  ax = plt.gca()
  ax.add_artist(circle)
  # Move the axes to the origin
  ax.spines['left'].set_position('zero')
  ax.spines['right'].set_color('none')
  ax.spines['bottom'].set_position('zero')
  ax.spines['top'].set_color('none')
  ax.xaxis.set_ticks_position('bottom')
  ax.yaxis.set_ticks_position('left')
  # Expand the plot
  xbottom, xtop = plt.xlim()
  ybottom, ytop = plt.ylim()
  size = max(1, xtop, ytop, -xbottom, -ybottom)
  size = size * 1.1  # Expand a little to make sure they're all in view
  plt.ylim(-size, size)
  size *= 4./3 # Adjust for aspect ratio
  plt.xlim(-size, size)
  plt.tight_layout()
  # Show the plot
  plt.show()

coef = sig.cheby1(N=4, rp=3, Wn=10, btype='lowpass', fs=1e3, output='zpk')
print(coef)
plot(coef[0], coef[1], coef[2])
#plot([.5], [2j], 1)
