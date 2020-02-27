#include "IIR.h"

double IIRfilter::Process(double sample){
    double in  = 0;
    double out = 0;
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

void IIRfilter::Reset(double val=0.){
    double a = 1;
    for(int i = 0; i < len; ++i){
        a += h[2*i];
    }
    // Calculate the steady-state internal value
    val = val * h[0] / a;
    // Reset the internal state
    for(int i = 0; i < len; ++i){
        x[i]=val;
    }
}

IIRfilter::IIRfilter(const double * coef, uint8_t size){
    len = size / (2*sizeof(double)) - 1;
    h = coef;
    x = new double[len];
    for(i = 0; i < len; ++i){
        x[i]=0;
    }
    i = 0;
}

IIRfilter::IIRfilter(const IIRfilter &copy){
    len = copy.len;
    h = copy.h;
    x = new double[len];
    for(i = 0; i < len; ++i){
        x[i]=0;
    }
    i = 0;
}

IIRfilter::~IIRfilter(void){
    delete x;
    // Assume h is constant and doesn't need deletion
}
