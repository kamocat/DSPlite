/* Finite Impulse Response Filter
 * 
 */
const float exp_decay[] = {1, .5, .25, .125, .0625, .0313, .0155, .00775, .00387};

/* IIR
 * Handmade exponential - should match above
 */
const float exp_decay2[] = {1, 1, -.5, 0};


/*  Experiment filter*/
const float experiment[] = {1, 1,0, 0,0, 0,-0.5, 0};

/*  Infinte Impulse Response Filter
Butterworth
Order: 2
Type: lowpass
Corner Frequency: 50Hz
*/
const float butter_50hz[] = {1.0, 0.020083365564211232,-1.5610180758007182, 0.040166731128422464,0.6413515380575631, 0.020083365564211232};

/*  Infinte Impulse Response Filter
Chebyshev type 1
Order: 8
  Type: lowpass
Ripple: 3
Corner Frequencies: 100
*/
const float cheby1_100hz[] = {1.0, 6.64434595243574e-07,-6.8842192436286105, 5.315476761948592e-06,21.41746642307788, 1.8604168666820074e-05,-39.257560232277044, 3.720833733364015e-05,46.31667955649944, 4.651042166705018e-05,-35.99433114433344, 3.720833733364015e-05,17.98991409202755, 1.8604168666820074e-05,-5.28816672419333, 5.315476761948592e-06,0.7004575387633586, 6.64434595243574e-07};
