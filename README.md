# DSPlite
A low-memory library for real-time signal conditioning, made for Arduino and Adafruit Feather m0

## Why another signal-processing library?
Many signal-processing libraries focus on FFT and frequency-domain manipulations. Although this is very powerful, it is also computationally intensive and is difficult to do real-time. This computation is doubled if you want to get the signal back to the time-domain.

On the other hand, realtime filtering libraries don't seem to go far enough. Most of them only do first and second-order filters. See my [literature review](https://github.com/kamocat/DSPlite/blob/master/literature_review.md#low-order-filtering).

There were three notable exceptions:
[Sebastian Nilsson](https://github.com/sebnil/FIR-filter-Arduino-Library/tree/master/src) and [Leeman Geophysical LLC](https://github.com/LeemanGeophysicalLLC/FIR_Filter_Arduino_Library) both made realtime libraries for finite impulse response filtering, but did not provide any implmentation for the more compact infinite impulse response filtering.
[Pieter P.](https://github.com/tttapa/Filters) made a very nice filtering library, opting for creating all the filters at run-time. He has provided an implementation of Butterworth, but not Chebyshev or Elliptic.

## How to use:
1. Record the signal that you plan to filter. (Record enough that you capture the big picture. A few thousand samples may be sufficient.)
2. Decided what you want to do with it:
    - Remove noise: Use a low-pass filter
    - Remove DC offset: Use a high-pass filter
    - Take the derivative? Use Savitsky-Golay
3. Use the filter design tool (dsplite.py) to select and test a filter
4. Include the filter in the Arduino code

## Installation:
This library should be installed in your Arduino libraries directory. 

## Features
- Linear Regression
- Finite Impulse Response filtering
- Infinite Impuslse Response filtering
    - Direct Form II (most effecient)
    - Cascaded second-order systems (least numerical errors)
- Python script to create filter coeffecients
    - Chebyshev
    - Butterworth
    - Elliptic
    - Savitsky-Golay
- Low-memory implementation: filter coeffecients are stored in program memory
- Real-time processing: Filter data as you collect it. No need to store arrays of data.


## Expectations
- Your Arduino either has a 1-cycle 32-bit multiply (like the m0) or has ample time to perform calculations. (An AVR core will take several hundred cycles [per floating point operation](https://people.ece.cornell.edu/land/courses/ece4760/Math/Floating_point/index.html), which can mean several milliseconds processing per sample. If you need speed in this situation, you should consider [fixed-point arithmatic](https://ucexperiment.wordpress.com/2015/03/31/avr-gcc-fixed-point-vs-floating-point-comparison).)
- You are sampling data at a fixed rate. If you do not know your sampling rate, please find out. Sampling rate is the number of times per second that you are collecting data.
- You have examined some of the data you want to filter, and have determined what you want to do with it (remove noise, remove DC offset, find the slope, etc). If you have already tried the filter in post-processing and want to move it the embedded context, even better.

## Not included
- Fourier Transforms (FFT): Use one of the many FFT libraries available.
- Resampling: Use a For() loop.
- Signal generation: Use the math library for sine() or whatever you need.
- Peak-detection: You can design a filter for local peak detection, but you must know something about the frequency components of the signal. Savitsky-Golay with a second-derivative might be a nice choice.
- Dynamic filter generation: Filters here are designed to be low-memory, which puts them in flash storage rather than RAM. This means they must be predefined before you compile. The side-effect of this is we can define the filters using Python and test them on captured data to see if they actually do what we want, before deploying them onto a microcontroller.
