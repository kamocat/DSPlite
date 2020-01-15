#include "IIR.h"

float IIRfilter::Process(float sample){
    float in  = 0;
    float out = 0;
    uint8_t j = 2;
    uint8_t k;
    uint8_t len2 = len * 2 + 2;
    
    for(k = i; k < len; --k){
        in  -= h[j++] * x[k];
        out += h[j++] * x[k];
    }
    
    for(k=len-1; k > i; --k){
        in  -= h[j++] * x[k];
        out += h[j++] * x[k];
    }
    if( i == (len-1) ){
        i = 0;
    } else {
        ++i;
    }
    // h[0] might not be 1 if the filter wasn't normalized
    in  += sample * h[0]; 
    x[i] = in;
    out += in * h[1];
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
    len = size / (2*sizeof(float)) - 1;
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
