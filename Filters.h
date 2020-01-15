/* Finite Impulse Response Filter
 * 
 */
const float exp_decay[] = {1, .5, .25, .125, .0625, .0313, .0155, .00775, .00387};

/* IIR
 * Handmade exponential - should match above
 */
const float exp_decay2[] = {1, 1, -.5, 0};



/*  Infinte Impulse Response Filter
Butterworth
Order: 2
Type: lowpass
Corner Frequency: 50Hz
*/
const float butter_50hz[] = {1.0, 0.020083365564211232,-1.5610180758007182, 0.040166731128422464,0.6413515380575631, 0.020083365564211232};
