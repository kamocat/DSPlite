
/*  Infinte Impulse Response Filter
Chebyshev type 1
Order: 5
  Type: lowpass
Ripple: 3
Corner Frequencies: 10
*/
const double cheby1_10hz[] = {1.0, 1.8836535e-09,-4.9589944, 9.418267e-09,9.84167, 1.8836534e-08,-9.770898, 1.8836534e-08,4.85277, 9.418267e-09,-0.9645474, 1.8836535e-09};

/*  Finite Impulse Response Filter
Savitsky-Golay
Window: 17
Order: 3
Derivative: 1
*/
const double savgol[] = {-0.032163743,0.0042139664,0.027648779,0.03998968,0.043085657,0.03878569,0.028938768,0.0153938765,6.071532e-18,-0.0153938765,-0.028938768,-0.03878569,-0.043085657,-0.03998968,-0.027648779,-0.0042139664,0.032163743};
