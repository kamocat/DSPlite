print("Loading numpy...")
import numpy as np
print("Done. Loading scipy..,")
import scipy.signal as sig
import scipy.fft as fft
print("Done. Loading pyplot...")
import matplotlib.pyplot as plt

print("Done. Importing data...")
data = np.loadtxt("data.csv")
print("Done. Calculating fft...")
f = fft.rfft(data)
g = np.zeros(f.shape)
g[:30]=1
g = np.multiply(g,f)
print("Done. Plotting data...")
plt.semilogy(np.absolute(f))
plt.semilogy(np.absolute(g))
plt.show()
print("Done. Applying filter...")
filt = fft.irfft(g)
plt.plot(data)
plt.plot(filt)
print("Done.")
plt.show()
