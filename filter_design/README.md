# Filter Design Assistant

This folder contains a Python script to help you design filters.
I've included some sample data so you can play around. When you collect your data, it should be in this format 
(each number on a new line, no extra information).

## Getting started
This script uses Python 3.
Ensure you have installed the python3 libraries for scipy, numpy, and matplotlib.
You can do this using the package manager of your choice. If you have python3-pip, this might be
`python3-pip install numpy scipy matplotlib`

Now you're ready to use the filter design tool.

In a terminal, type
`python3 dsplite.py data.csv`
And follow the instructions.

For this data, I found good results with
- passband frequency of 0.02 Hz
- stopband frequency of 0.03 Hz
- stopband attenuation of 30 dB
- passband ripple of 0.1 dB
- elliptic filter (Option #4)

Once you have a filter you like, you can save the coeffecients to a header file (Filters.h) which you will 
copy to your sketch folder and include with `#include "Filters.h".

Note that unless you specify the maximum frequency, the program assumes the maximum frequency is 1.
You should be able to hover over the frequency plot and read the x values to determine which frequencies to filter.
