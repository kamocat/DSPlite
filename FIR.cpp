#include "FIR.h"

FIRfilter::FIRfilter(int length){
    int j;
    for(j = 0; length; length=length>>1);
    maxlen = 2<<j;
    mask = maxlen-1;
    data = new float[length];
    Reset();
}

void FIRfilter::Reset(void){
    len = 0;
    i = 0;
}

void FIRfilter::Append(float sample){
    data[i]=sample;
    i = mask & (i+1);
    if( len < maxlen )
        ++len;
}

float FIRfilter::Convolve(float * h, int length){
    int m = (length<len)?length:len;
    int k = i + 1;
    float sum = 0;
    // Convolve with the recorded data
    int j;
    for( j = 0; j < m; ){
        sum += h[j++]*data[--k];
        k &= mask;
    }
    // Extend the tail of the data
    for(; j<length;){
        sum += h[j++]*data[k];
    }
    return sum;
}

FIRfilter::~FIRfilter(void){
    delete data;
}
