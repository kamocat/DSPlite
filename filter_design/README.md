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
Open a terminal and type  
`python3 dsplite.py data.csv`

Once you have a filter you like, you can save the coeffecients to a header file (Filters.h) which you will 
copy to your sketch folder and include with `#include "Filters.h"`.

## Tuning the filter
You can play with the filter parameters and see what gives the best result. There's no one filter that will fix everything - it depends on what you're trying to do and what compromises you're willing to make. In general, a higher order means more delay between your input and output. You won't see more than 50dB attenuation because that's the dynamic range of the IEEE double-precision floating point mantissa. (These numbers are digital and not infinitely precise, so you will always see noise at 50dB below your loudest signal. This is the lower limit - you can't reduce noise past this point, but it can be amplified.)

Note that unless you specify the sample frequency, the program assumes the maximum frequency is 1.
You should be able to hover over the frequency plot and read the x values to determine which frequencies to filter.

### Example tuning
For this data, I wanted to get rid of the quantization error from the ADC, but keep the general shape of the waveform. This means I need a low-pass filter. I used the frequency components graph as a guide, and picked a frequency where my signal faded into noise. Then I played with the parameters a little. Some things surprised me. For example, even orders on the elliptic filter messed with my DC offset, even with the passband ripple set really low. After several iterations, I settled on these settings:
- passband frequency of 0.02 Hz
- stopband frequency of 0.03 Hz
- stopband attenuation of 30 dB
- passband ripple of 0.1 dB
- elliptic filter (Option #4)

### Things to try
- Set the passband higher than the stopband.
    - What happens to the shape of the frequency response?
    - What happens to the output?
- Set the passband ripple really small (0.01 dB) and the stopband attenuation really large (100 dB).
    - What happens to the filter order?
    - How much does the filtered signal lag behind the original?



Now you're ready to try with your own data! Collect some data and write it to a file. Then run the program.

`python3 dsplite.py MY_DATA -f SAMPLE_FREQUENCY`

where MY_DATA is whatever you named your saved data, and SAMPLE_FREQUENCY is the rate that you recorded the data.

## Advanced usage
This script only designs lowpass or highpass filters, but its also possible to create notch and bandpass filters with the scipy.signal library. You can read more about it in the [scipy documentation](https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html#scipy.signal.butter).
