#include "IIR.h"

float IIRfilter::Process(float sample){
    float in  = 0;
    float out = 0;
    uint8_t j = 2;
    ++i;
    while(i){
        in  += h[j++] * x[--i];
        out += h[j++] * x[i];
    }
    uint8_t len2 = len * 2;
    i = len;
    while(j<len2){
        in  += h[j++] * x[--i];
        out += h[j++] * x[i];
    }
    // h[1] might not be 1 if the filter wasn't normalized
    in  += sample * h[1]; 
    x[i] = sample;
    out += in * h[0];
    return out;
}

void IIRfilter::Reset(float val=0.){
    float a = 0;
    // Find the total gain of the denominator.
    for(i = 1; i < (2*len); i+=1){
        a += h[i];
    }
    // Calculate the steady-state condition of a one-element feedback
    // steady = input + steady*(a-1) ===> steady = input / (2-a)
    val = val / (2-a);
    // Reset the internal state
    for(i = 0; i < len; ++i){
        x[i]=val;
    }
    i = 0;
}

IIRfilter::IIRfilter(const float * coef, uint8_t size){
    len = size / 2;
    h = coef;
    x = new float[len];
    for(i = 0; i < len; ++i){
        x[i]=0;
    }
    i = 0;
}

IIRfilter::IIRfilter(const IIRfilter &copy){
    len = copy.len;
    h = copy.h;
    x = new float[len];
    for(i = 0; i < len; ++i){
        x[i]=0;
    }
    i = 0;
}

IIRfilter::~IIRfilter(void){
    delete x;
    // Assume h is constant and doesn't need deletion
}
