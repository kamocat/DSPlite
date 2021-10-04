#include "SOS.h"
#include <stdlib.h>

double kernel(double in, const struct SOSystem * coef, double * mem){
    in *= coef->a0;
    in -= mem[0] * coef->a1;
    in -= mem[1] * coef->a2;
    double out = in * coef->b0;
    out += mem[0] * coef->b1;
    out += mem[1] * coef->b2;
    mem[1] = mem[0];
    mem[0] = in;
    return out;
}

double SOSProcess(struct SOSfilter * s, double sample){
    double y = sample;
    for(int i = 0; i < s->len; ++i){
        // Each stage processes the output of the previous
        y = kernel(y, s->h+i, s->x+i+i);
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

void SOSReset(struct SOSfilter * s, double val=0.){
    int k = 0;
    for(int i = 0; i < s->len; ++i){
        double z = val * s->h[i].a0 / (1 + s->h[i].a1 + s->h[i].a2);
        s->x[k++]=z; // first memory element
        s->x[k++]=z; // second memory element
        val = z * (s->h[i].b0 + s->h[i].b1 + s->h[i].b2);
    }
}

void SOSInit(struct SOSfilter * s, const struct SOSystem * coef, uint8_t size){
    s->len = size / (sizeof(struct SOSystem));
    s->h = coef;
    int len2 = s->len * 2;
    s->x = (double *)malloc( sizeof(double) * len2 );
    for(int i = 0; i < len2; ++i){
        s->x[i]=0;
    }
}

void SOSDelete(SOSfilter * s){
    free( s->x );
    // Assume h is constant and doesn't need deletion
}
