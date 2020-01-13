//test suite
#include "../LinearRegression.cpp"
#include "../IIR.h"
#include "../Filters.h"
#include <iostream>
#include <vector>
#include <cmath>

void TestLinearRegression(void);
float TestIIR(float);

int main( int argc, char ** argv){
    //TestLinearRegression();
    //TestRunningAverage();
    std::cout<<"Attenuation at 10 Hz: "<<TestIIR(10)<<"dB"<<std::endl;
    std::cout<<"Attenuation at 100 Hz: "<<TestIIR(100)<<"dB"<<std::endl;
    std::cout<<"Attenuation at 1 kHz: "<<TestIIR(1000)<<"dB"<<std::endl;
    return 0;
}

float TestIIR(float freq){
    IIRfilter filter(cheby1_100Hz, sizeof(cheby1_100Hz));
    float in_rms = 0;
    float rms = 0;
    float mean = 0;
    int size = 10000;
    freq = freq / 1000.;
    for( int i = 0; i < size; ++i){
        float x = sqrt(2)*sin(freq * i * 6.28);
        float y = filter.Process(x);
        rms += y*y;
    }
    rms = sqrt(rms/size);
    return 10*log10(rms);
}

void TestLinearRegression(void){
    
    std::cout<<"Testing Linear Regression... ";
    
    Regression lin;
    
    float m, b; // y = mx+b
    m = 15.67;
    b = 3.29;
    
    for( int i=0; i < 100; ++i ){
        float p = m*i+b;
        lin.Append(p);
    }
    
    float slope = lin.GetSlope();
    float offset = lin.GetOffset();
    
    float e = 0.001;    // tolerance
    if( (abs(slope - m) < e) && (abs(offset - b) < e) ){
        std::cout<<"Success!";
    } else {
        std::cout<<"Failure";
    }
    std::cout<<std::endl;
}
