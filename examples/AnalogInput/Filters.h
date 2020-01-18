
/*  Infinte Impulse Response Filter
Chebyshev type 1
Order: 4
  Type: lowpass
Ripple: 3
Corner Frequencies: 10
*/
const float cheby1_10hz[] = {1.0, 1.198806e-07,-3.9595377, 4.795224e-07,5.8832955, 7.1928355e-07,-3.887874, 4.795224e-07,0.9641188, 1.198806e-07};

/*  Finite Impulse Response Filter
Savitsky-Golay
Window: 17
Order: 3
Derivative: 1
*/
const float savgol[] = {-0.032163743,0.0042139664,0.027648779,0.03998968,0.043085657,0.03878569,0.028938768,0.0153938765,6.071532e-18,-0.0153938765,-0.028938768,-0.03878569,-0.043085657,-0.03998968,-0.027648779,-0.0042139664,0.032163743};
