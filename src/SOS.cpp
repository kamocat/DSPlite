#include "SOS.h"

double kernel(double in, const struct SOSystem &coef, double * mem){
    in *= coef.a0;
    in -= mem[0] * coef.a1;
    in -= mem[1] * coef.a2;
    double out = in * coef.b0;
    out += mem[0] * coef.b1;
    out += mem[1] * coef.b2;
    mem[1] = mem[0];
    mem[0] = in;
    return out;
}

double SOSfilter::Process(double sample){
    double y = sample;
    for(int i = 0; i < len; ++i){
        // Each stage processes the output of the previous
        y = kernel(y, h[i], x+i+i);
    }
    return y;
}

/** 
Steady-state equations::
  z = val*a0 - z(a1+a2)
  y = z*(b0 + b1 + b2)

Solving for z, we get::
  z = val * a0 / (1 + a1 + a2)
*/

void SOSfilter::Reset(double val=0.){
    int k = 0;
    for(int i = 0; i < len; ++i){
        double z = val * h[i].a0 / (1 + h[i].a1 + h[i].a2);
        x[k++]=z; // first memory element
        x[k++]=z; // second memory element
        val = z * (h[i].b0 + h[i].b1 + h[i].b2);
    }
}

SOSfilter::SOSfilter(const struct SOSystem * coef, uint8_t size){
    len = size / (sizeof(struct SOSystem));
    h = coef;
    int len2 = len * 2;
    x = new double[len2];
    for(int i = 0; i < len2; ++i){
        x[i]=0;
    }
}

SOSfilter::SOSfilter(const SOSfilter &copy){
    len = copy.len;
    h = copy.h;
    int len2 = len * 2;
    x = new double[len2];
    for(int i = 0; i < len2; ++i){
        x[i]=0;
    }
}

SOSfilter::~SOSfilter(void){
    delete x;
    // Assume h is constant and doesn't need deletion
}
