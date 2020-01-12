#include "RunningAverage.h"

RunningAverage::RunningAverage(int length)
    : FIRfilter(length){
    // Actually set maxlen to length
    // Although we have more memory allocated
    maxlen = length;
    sum = 0;
    data[i]=0;
}

float RunningAverage::Append(float sample){
    sum += sample - data[i];
    data[i]=sample;
    i = mask & (i+1);
    if( len < maxlen ){
        ++len;
    }
    return sum / len;
}

float RunningAverage::Average(void){
    return sum / len;
}

void RunningAverage::Reset(void){
    sum=0;
    i=0;
    data[i]=0;
    len=0;
}
