#include "FIR.h"

FIRfilter::FIRfilter(const float * coef, uint8_t size){
    len = (size / sizeof(float))-1;
    h = coef;
    x = new float[len];
    for(i = 0; i < len; ++i){
        x[i]=0;
    }
    i = 0;
}

FIRfilter::FIRfilter(const FIRfilter &copy){
    len = copy.len;
    h = copy.h;
    x = new float[len];
    for(i = 0; i < len; ++i){
        x[i]=0;
    }
    i = 0;
}

FIRfilter::~FIRfilter(void){
    delete x;
    // Assume h is constant and doesn't need deletion
}

void FIRfilter::Reset(float val=0.){
    // Reset the internal state
    for(i = 0; i < len; ++i){
        x[i]=val;
    }
    i = 0;
}

float FIRfilter::Process(float sample){
    float out = 0;
    uint8_t j = 1;
    uint8_t k;
    for(k=i; k<len; --k){
        out += h[j++] * x[k];
    }
    for(k=len-1; k > i; --k){
        out += h[j++] * x[k];
    }
    if( i == (len-1) ){
        i = 0;
    } else {
        ++i;
    }
    x[i] = sample;
    out += sample*h[0];
    return out;
}
