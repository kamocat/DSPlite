# DSPlite
A low-memory library for real-time signal conditioning, made for Arduino and Adafruit Feather m0

## Features
- Linear Regression
- Finite Impulse Response filtering
- Infinite Impuslse Response filtering
- Python script to create filter coeffecients
  - Chebyshev
  - Butterworth
  - Savitsky-Golay
- Low-memory implementation: filter coeffecients are stored in program memory
- Real-time processing: Filter data as you collect it. No need to store arrays of data.


## Expectations
- Your Arduino either has a 1-cycle floating-point multiply (like the m0) or has ample time to perform calculations. (An AVR core will take several hundred cycles [per floating point operation](https://people.ece.cornell.edu/land/courses/ece4760/Math/Floating_point/index.html), which can mean several milliseconds processing per sample. If you need speed in this situation, you should consider [fixed-point arithmatic](https://ucexperiment.wordpress.com/2015/03/31/avr-gcc-fixed-point-vs-floating-point-comparison).)
- You are sampling data at a fixed rate. If you do not know your sampling rate, please find out. Sampling rate is the number of times per second that you are collecting data.
- You have examined some of the data you want to filter, and have determined what you want to do with it (remove noise, remove DC offset, find the slope, etc). If you have already tried the filter in post-processing and want to move it the embedded context, even better.

## Not included
- Fourier Transforms (FFT)
- Kalman filtering
- Resampling
- Signal generation
- Peak-detection (Although you could design a filter to do this)
- Dynamic filter generation. Filters here are designed to be low-memory, which puts them in program storage. This means they must be predefined before you compile.
