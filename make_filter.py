# This script makes filters using scipy, for use in C++

import numpy as np
import scipy.signal as sig

# used for saving IIR filter system
def save_IIR(f, filtername, coef ):
  f.write(F'\nconst float {filtername}[] = {{')
  len = np.shape(coef)[1]-1
  for i in range(len):
    f.write(F'{coef[1][i]}, {coef[0][i]},')
  f.write(F'{coef[1][len]}, {coef[0][len]}}};\n')
  f.close()

def test_filter( coef ):
  import matplotlib.pyplot as plt
  a = np.zeros(20);
  a[0]=100;
  b = sig.lfilter(coef[0], coef[1], a)
  plt.plot(b)
  plt.show()

def cheby():
  # Example for Chebyshev type 1 filter
  # You can view other filters at https://docs.scipy.org/doc/scipy/reference/signal.html#matlab-style-iir-filter-design
  filter_type = 'Chebyshev type 1'
  order = 8
  ripple = 3
  btype = 'lowpass'
  sample_frequency = 1e3
  corner_frequencies = 100
  ba = sig.cheby1(N=order, rp=ripple , Wn=corner_frequencies, 
                  btype=btype, fs=sample_frequency, )
  test_filter(ba)
  #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"""\n/*  Infinte Impulse Response Filter\n{filter_type}\nOrder: {order}
  Type: {btype}\nRipple: {ripple}\nCorner Frequencies: {corner_frequencies}\n*/""")
  
  # Write the filter coeffecients
  save_IIR(f, 'cheby1_100hz', ba )

def butterworth():
  # Example for Butterworth
  # You can view other filters at https://docs.scipy.org/doc/scipy/reference/signal.html#matlab-style-iir-filter-design
  filter_type = 'Butterworth'
  order = 2
  btype = 'lowpass'
  sample_frequency = 1e3
  corner = 50
  ba = sig.butter(N=order, Wn=corner, btype=btype, fs=sample_frequency, )
  test_filter(ba)
  #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"""\n/*  Infinte Impulse Response Filter\n{filter_type}\nOrder: {order}
Type: {btype}\nCorner Frequency: {corner}Hz\n*/""")
  
  # Write the filter coeffecients
  save_IIR(f, 'butter_50hz', ba )

def experiment():
  # This is for testing custom filters
  # Probably only used for debugging
  ba = ((1, 0, 0, 0),(1,0,0,-.5))
  test_filter(ba)
  #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"\n/*  Experiment filter*/")
  
  # Write the filter coeffecients
  save_IIR(f, 'experiment', ba )

def savgol():
  # Example for Savitzky-Golay
  # You can view documentation at https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.savgol_coeffs.html
  filter_type = 'Savitsky-Golay'
  window = 17
  order = 3
  dn = 1
  coef = sig.savgol_coeffs(window, order, dn)
  #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"""\n/*  Finite Impulse Response Filter\n{filter_type}
Window: {window}\nOrder: {order}\nDerivative: {dn}\n*/""")
  
  # Write the filter coeffecients
  f.write(F'\nconst float savgol[] = {{')
  len = coef.shape[0]-1
  for i in range(len):
    f.write(F'{coef[i]},')
  f.write(F'{coef[len]}}};\n')
  f.close()

#butterworth()
#cheby()
#experiment()
savgol()
