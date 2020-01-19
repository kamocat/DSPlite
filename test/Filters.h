/* Cascaded Second Order System Filter
Chebyshev type 1
Order: 4
Type: lowpass
Ripple: 3
Corner Frequencies: 10
*/
const struct SOSystem cheby1_10hz[] = {
{1.198806e-07,2.397612e-07,1.198806e-07,1.0,-1.973723,0.97448725},
{1.0,2.0,1.0,1.0,-1.9858147,0.9893601}
};


/*  Cascaded Second Order System
Butterworth
Order: 2
Type: lowpass
Corner Frequency: 50Hz
*/
const struct SOSystem butter_50hz[] = {
{0.020083366,0.040166732,0.020083366,1.0,-1.5610181,0.6413515}
};
