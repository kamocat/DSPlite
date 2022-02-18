#include "Histogram.h"

Histogram::Histogram(uint16_t l){
    size = l;
    bin = new int16_t[size];
    Reset();
}

Histogram::Histogram(const Histogram &copy){
    size = copy.size;
    bin = new int16_t[size];
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
    sum += sample;
    if( count < size ){
        bin[count++]=sample;
        return;
    } else if( count == size ){
        offset = sum/(count+1) - size/2;
        int16_t * tmp = new int16_t[size];
        for(auto i=0; i<count; ++i){
            int16_t x = bin[i] - offset;
            if(x<0)
                tmp[0]++;
            else if(x>=size)
                tmp[size-1]++;
            else
                tmp[x]++;
        }
        delete bin;
        bin = tmp;
    }
    int16_t x = sample - offset;
    if( x <= 0 ){
        bin[0] = bin[0] + 1;
    } else if( x >= (size-1) ){
        bin[size-1] += 1;
    } else {
        bin[x] = bin[x] + 1;
    }
    ++count;
}

int16_t Histogram::Median(void){
    int i;
    int16_t x = 0;
    if(count<=size){
        this->Sort();
        return bin[count/2];
    }
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

int16_t Histogram::Mean(void){
    return(sum/count);
}

void Histogram::Sort(void){
    if(count>size)
        return;
    for(int i=0; i<count; ++i){
        int16_t x = bin[i];
        int j = i-1;
        while((j>=0)&&(bin[j]>x)){
            bin[j+1]=bin[j];
            --j;
        }
        bin[j+1]=x;
    }
}

#ifdef DEBUG_HISTOGRAM
#include <iostream>
bool Histogram::Sorted(void){
    if(count>size)
        return false;
    for(int i=0; i<count-1; ++i){
        if(bin[i]>bin[i+1])
            return false;
    }
    return true;
}


void Histogram::Print(void){
    if(count > size){
        for(int i=0; i<size; ++i){
            std::cout<<'\n'<<i+offset<<":\t";
            for(int j=0; j<bin[i]; ++j){
                std::cout<<'*';
            }
        }
    }else{
        for(int i=0; i<count; ++i){
            std::cout<<bin[i]<<", ";
        }
    }
    std::cout<<std::endl;
}
#endif
