# DSPlite
A low-memory library for real-time signal conditioning, made for Arduino and Adafruit Feather m0

## Expectations
I am assuming that your Arduino either has a 1-cycle floating-point multiply (like the m0) or has ample time to perform calculations. (An AVR core will take several hundred cycles [per floating point operation](https://people.ece.cornell.edu/land/courses/ece4760/Math/Floating_point/index.html), which can mean several milliseconds processing per sample. If you need speed in this situation, you should consider [fixed-point arithmatic](https://ucexperiment.wordpress.com/2015/03/31/avr-gcc-fixed-point-vs-floating-point-comparison).)

I am also assuming that you are sampling data at a fixed rate.

## What this includes
- Slope-finding methods
  - Linear Regression
  - Average of differences
- Signal Smoothing
  - Running Average
  - Savitsky-Golay (ToDo)
  - Chebyshev low-pass filter (ToDo)

## Not included
- Fourier Transforms (FFT)
  This is both memory-intensive and processor-intensive, and will probably not give you the performance you want. If you need frequency analysis, you should pick an ARM processor with DSP acceleration and use the CMSIS libraries. The STM32F7 might be a good choice. Or you could use an external DSP chip or FPGA.
