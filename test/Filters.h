
/*  Cascaded Second-Order System
Passband: 0.03Hz, 0.1dB ripple.
Stopband: 0.02Hz, 30.0dB attenuation.
*/
const struct SOSystem example_elliptic[] = {
{0.004490986834406868,0.004490986834406868,0.0,1.0,-0.9532728864451816,0.0},
{1.0,-1.987524684443374,1.0,1.0,-1.949238906443125,0.9526717874462354},
{1.0,-1.9937223855860777,0.9999999999999997,1.0,-1.9855619799361008,0.9899471884661526}
};

const struct SOSystem simple[] = {
{2, 0, 0, 1, 0.5, .5},
{2, 0, 0, 1, 0.5, .5},
};

const double simple2[] = {
1, 3, .5, 0, .5, 0, .5, 0, .5, 0,
};
