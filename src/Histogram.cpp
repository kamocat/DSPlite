#include "Histogram.h"
#include <iostream>

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
    count = 0;
    offset = 0;
    sum = 0;
}

void Histogram::Process(int16_t sample){
    sum += sample;
    if( count < size ){
        bin[count++]=sample;
        return;
    } else if( count == size ){
        offset = sum/(count+1) - size/2;
        int16_t * tmp = new int16_t[size];
        for(auto i=0; i<size; ++i){
            tmp[i]=bin[i];
            bin[i]=0;
        }
        for(auto i=0; i<size; ++i){
            int16_t x = tmp[i] - offset;
            if(x<0)
                ++bin[0];
            else if(x>=size)
                ++bin[size-1];
            else
                ++bin[x];
        }
        delete tmp;
    }
    int16_t x = sample - offset;
    if( x < 0 ){
        ++bin[0];
    } else if( x >= size ){
        ++bin[size-1];
    } else {
        ++bin[x];
    }
    ++count;
}

int16_t Histogram::Median(void){
    int i;
    int16_t x = 0;
    int mid = count/2;
    if(count<=size){
        Sort();
        x = bin[mid];
        x += bin[count-mid];
        return x/2;
    }
    for(i=0; i < size; ++i){
        x += bin[i];
        if( x >= mid)
            break;
    }
    return (i + offset);
}

int16_t Histogram::Mode(void){
    //FIXME: Doesn't work correctly for count<=size
    int16_t max = 0;
    for(int i = 1; i < size-1; ++i){
        if( bin[i] > bin[max] )
            max = i;
    }
    return (max + offset);
}

int32_t Histogram::Variance(void){
    if(count <= size){ // True standard deviation
        int32_t m = Mean();
        uint32_t a = 0;
        for(int i=0; i<count; ++i){
            int32_t s = bin[i]-m;
            s = s*s;
            a += s;
        }
        return a/count;
    } else{ // Outliers truncated (underestimate)
         int16_t o = Mean() - offset;
         uint32_t a = 0;
         for(int i=0; i<size; ++i){
             int32_t s = (i-o);
             s = s*s;
             a += bin[i]*s;
         }
         return a/count;
    }
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
