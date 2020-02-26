#!/usr/bin/python3
print("Welcome to the DSPLite Filter Design Tool.")
import numpy as np
from numpy import pi
import scipy.signal as sig
import scipy.fft as fft
import matplotlib.pyplot as plt

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('filename', help='Sample data for designing and testing filter. Should contain a single column of numeric values.')
parser.add_argument('-f', help='Sample frequency (how fast the data was recorded, in samples per second)', type=float)
args = parser.parse_args()
print("Loading file...")
nyquist = 1/pi
if args.f:
  nyquist = nyquist * args.f/2

data = np.loadtxt(args.filename)

# Plot the input data
plt.subplot(121)
plt.plot(data)
plt.title("Input Waveform")
plt.subplot(122)
f = fft.rfft(data)
w = np.linspace(0, nyquist*pi, len(f))
plt.semilogy(w, np.absolute(f))
plt.title("Frequency Components")
plt.show()

def get_params():
  wp = float(input("Passband Frequency? "))/(nyquist*pi)
  ws = float(input("Stopband Frequency? "))/(nyquist*pi)
  gstop = float(input("Min Stopband Attenuation? (in dB) "))
  gpass = float(input("Max Passband Ripple? (in dB) "))
  params = dict()
  params['ws']=ws
  params['wp']=wp
  params['gstop']=gstop
  params['gpass']=gpass
  return(params)

def design(params):
  print(params)
  while(1): # Loop until we're happy with our parameters
    wp = params['wp']
    ws = params['ws']
    gstop = params['gstop']
    gpass = params['gpass']
    print(params)
    if wp < ws:
      btype = 'lowpass'
    else:
      btype = 'highpass'
    print(f'This is a {btype} filter.')
    
    # Calculate the orders of each filter type
    cheby1 = sig.cheb1ord(  
          params['wp'], params['ws'], params['gpass'], params['gstop'])
    cheby2 = sig.cheb2ord(
          params['wp'], params['ws'], params['gpass'], params['gstop'])
    butter = sig.buttord(
          params['wp'], params['ws'], params['gpass'], params['gstop'])
    elliptic = sig.ellipord(
          params['wp'], params['ws'], params['gpass'], params['gstop'])
    
    x = int(input(F'''Please select an implementation:
    1: Chebyshev type I ({cheby1[0]} order, corner at {cheby1[1]*nyquist} Hz)
    2: Chebyshev type II ({cheby2[0]} order, corner at {cheby2[1]*nyquist} Hz)
    3: Butterworth ({butter[0]} order, corner at {butter[1]*nyquist} Hz)
    4: Elliptic ({elliptic[0]} order, corner at {elliptic[1]*nyquist} Hz)
    5: Choose new design constraints
    '''))
    if x == 1:
      sos = sig.cheby1(N=cheby1[0], rp=params['gpass'] , Wn=cheby1[1], 
                      btype=btype, output='sos' )
    elif x == 2:
      sos = sig.cheby2(N=cheby2[0], rs=params['gstop'] , Wn=cheby2[1], 
                      btype=btype, output='sos' )
    elif x == 3:
      sos = sig.butter(N=butter[0], Wn=butter[1], 
                      btype=btype, output='sos' )
    elif x == 4:
      sos = sig.ellip(N=elliptic[0], rp=params['gpass'], rs=params['gstop'], 
      Wn=elliptic[1], btype=btype, output='sos' )
    else:
      params = get_params()
      continue
    return(sos,params) #Break out of the loop


params = get_params()
while(1): # Loop until we're happy with our filter
  sos,params = design(params)

  # Plot frequency response and group delay
  ax = plt.subplot(121)
  pulse = np.zeros(1024)
  pulse[0]=1
  h = np.absolute(fft.rfft(sig.sosfilt(sos, pulse)))
  w = np.linspace(0,1,len(h))
  plt.semilogy(w,h)
  plt.title("Frequency Response")
  ax = plt.subplot(122)
  w,grp = sig.group_delay(sig.sos2tf(sos))
  w = np.linspace(0,1,len(w))
  ax.plot(w,grp)
  plt.title("Group delay")
  plt.show()
  
  x = input("Try this filter? y/n (y) ") 
  if len(x)!=0 and x[0]=='n':
    continue #pick a new filter
  
  #Plot before/after for time and frequency domain
  zi = sig.sosfilt_zi(sos) # Set initial conditions
  # Use the initial conditions to produce a sane result (not jumping from 0)
  clean, zo = sig.sosfilt(sos, data, zi=zi)
  w = np.linspace(0, nyquist*pi, len(f))
  plt.subplot(121)
  plt.plot(data, label="Unfiltered")
  bottom,top = plt.ylim()
  plt.title("Signal")
  # Despite the initial conditions, this still starts near 0
  plt.plot(clean, label="Filtered")
  plt.ylim(bottom,top)
  plt.legend(loc="best")
  plt.subplot(122)
  plt.semilogy(w,np.absolute(f), label="Unfiltered")
  g = fft.rfft(clean)
  plt.semilogy(w,np.absolute(g), label="Filtered")
  plt.title("Frequency Composition")
  plt.legend(loc="best")
  plt.show()
  
  x = input("Output to file? y/n ")
  if len(x)==0 or x[0]=='y':
    break # Save this filter

fn = input("filter name: ")

def save_sos(params, filtername, coef ):
   #Open the header file to save this in
  f = open('Filters.h', 'a')
  
  # Write the parameters in a comment
  f.write(F"""\n/*  Cascaded Second-Order System
Passband: {params['ws']*nyquist}Hz, {params['gpass']}dB ripple.
Stopband: {params['wp']*nyquist}Hz, {params['gstop']}dB attenuation.
*/""")
  # Write the coeffecients in a constant struct array
  n = np.shape(coef)[0]
  f.write(F'\nconst struct SOSystem {filtername}[] = {{')
  for i in range(n):
    f.write('\n{');
    for j in range(6):
      f.write(F'{coef[i][j]!r}')
      if( j < 5 ):
        f.write(',')
      elif( i < (n-1) ):
        f.write('},')
      else:
        f.write('}\n')
  f.write('};');
  f.close()

save_sos(params, fn, sos)
