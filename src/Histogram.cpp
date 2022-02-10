#include "Histogram.h"

Histogram::Histogram(uint16_t l){
    size = l;
    bin = new uint16_t[size];
    Reset();
}

Histogram::Histogram(const Histogram &copy){
    size = copy.size;
    bin = new uint16_t[size];
    Reset();
}

Histogram::~Histogram(void){
    delete bin;
}

void Histogram::Reset(void){
    for(int i = 0; i < size; ++i){
        bin[i] = 0;
    }
    count = 0;
    offset = 0;
}

void Histogram::Process(int16_t sample){
    ++count;
    int16_t x = sample - offset;
    if( 1 == count ){
        x = size / 2;
        offset = sample - size;
        bin[x] = bin[x]+1;
    } else if( x <= 0 ){
        bin[0] = bin[0] + 1;
        //TODO: Rebalance if more than half in the lowest bin
    } else if( x >= (size-1) ){
        bin[size-1] = bin[size-1] + 1;
        //TODO: Rebalance if more than half in the highest bin
    } else {
        bin[x] = bin[x] + 1;
    }
}

int16_t Histogram::Median(void){
    int i;
    int16_t x = 0;
    for(i=0; i < size; ++i){
        x += bin[i];
        if( x >= count/2)
            break;
    }
    return (i + offset);
}

int16_t Histogram::Mode(void){
    int16_t max = 0;
    for(int i = 1; i < size; ++i){
        if( bin[i] > bin[max] )
            max = i;
    }
    return (max + offset);
}

int16_t Histogram::StandardDeviation(void){
     int upper, lower, i;
     uint16_t x = 0;
     //68.2% of the values are within 1 standard deviation of the mean
     uint16_t tail = (1-0.682)*0.5;
     tail *= count;
     for(i=0; i<size; ++i){
         x += bin[i];
         if(x > tail){
             lower = i;
             break;
         }
     }
     x = 0;
     for(i=size-1; i; --i){
         x += bin[i];
         if(x > tail){
             upper = i;
             break;
         }
     }
     return( (upper-lower)/2);
}








