#!/usr/bin/python3
print("Welcome to the DSPLite Filter Design Tool.")
fname = input("Please enter a logfile to load.")
import scipy.signal as sig
#FIXME: Load the file

fs = float(input("Sample frequency? "))
nyquist = fs/2
x = input("Show the waveform? y/n (y) ")

print("Computing the FFT...")
#FIXME: Display and load the fft

wp = float(input("Passband Frequency? "))/nyquist
ws = float(input("Stopband Frequency? "))/nyquist
gstop = float(input("Min Stopband Attenuation? (in dB) "))
gpass = float(input("Max Passband Ripple? (in dB) "))

cheby1 = sig.cheb1ord(wp, ws, gpass, gstop)
cheby2 = sig.cheb2ord(wp, ws, gpass, gstop)
butter = sig.buttord(wp, ws, gpass, gstop)
elliptic = sig.ellipord(wp, ws, gpass, gstop)

x = int(input(F'''Please select an implementation:
1: Chebyshev type I ({cheby1[0]} order, corner at {cheby1[1]*nyquist} Hz)
2: Chebyshev type II ({cheby2[0]} order, corner at {cheby2[1]*nyquist} Hz)
3: Butterworth ({butter[0]} order, corner at {butter[1]*fs} Hz)
4: Elliptic ({elliptic[0]} order, corner at {elliptic[1]*fs} Hz)
5: Choose new design constraints
'''))


#FIXME: Plot frequency response and group delay

x = input("Try this filter? y/n (y) ") 

#FIXME: Plot before/after for time and frequency domain

x = input("Output to file? y/n ")

fn = input("filename")
