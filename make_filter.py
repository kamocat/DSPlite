# This script makes filters using scipy, for use in C++

import numpy as np
import scipy.signal as sig

# used for saving IIR filter system
def save_IIR(f, filtername, coef ):
  f.write(F'\nconst float {filtername}[] = {{')
  len = np.shape(coef)[1]-1
  for i in range(len):
    f.write(F'{coef[0][i]}, {coef[1][i]},')
  f.write(F'{coef[0][len]}, {coef[1][len]}}};\n')
  f.close()


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
  
  #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"""\n/*  Infinte Impulse Response Filter\n{filter_type}\nOrder: {order}
  Type: {btype}\nRipple: {ripple}\nCorner Frequencies: {corner_frequencies}\n*/""")
  
  # Write the filter coeffecients
  save_IIR(f, 'cheby1_100hz', ba )
  f.close()

def butterworth():
  # Example for Butterworth
  # You can view other filters at https://docs.scipy.org/doc/scipy/reference/signal.html#matlab-style-iir-filter-design
  filter_type = 'Butterworth'
  order = 1
  btype = 'lowpass'
  sample_frequency = 1e3
  corner = 50
  ba = sig.butter(N=order, Wn=corner, btype=btype, fs=sample_frequency, )
  
  #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"""\n/*  Infinte Impulse Response Filter\n{filter_type}\nOrder: {order}
Type: {btype}\nCorner Frequency: {corner}Hz\n*/""")
  
  # Write the filter coeffecients
  save_IIR(f, 'butter_50hz', ba )
  f.close()
  
butterworth()
