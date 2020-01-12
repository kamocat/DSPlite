//test suite
#include "../LinearRegression.cpp"
#include "../RunningAverage.cpp"
#include "../IIR.h"
#include "../Filters.h"
#include <iostream>
#include <vector>
#include <cmath>

void TestLinearRegression(void);
void TestRunningAverage(void);
void TestIIR(void);

int main( int argc, char ** argv){
    //TestLinearRegression();
    //TestRunningAverage();
    TestIIR();
    return 0;
}

void TestIIR(void){
    IIRfilter f(bessel1, sizeof(bessel1));
    int size = 10;
    for( int i = 0; i < size; ++i){
        std::cout<<f.Process(i%2)<<" ";
    }
}

void TestRunningAverage(void){
    std::cout<<"Testing Running Average... ";
    int size = 10;
    RunningAverage run_avg(size);
    // Make an array of random numbers
    float num;
    float sum = 0;
    for( int i = 0; i < size; ++i ){
        num = i+1;
        float tmp = run_avg.Append(num);
        std::cout<<tmp<<", ";
        sum += num;
    }
    sum /= size;
    if( sum == run_avg.Average() ){
        std::cout<<"Success!";
    } else {
        std::cout<<"Failure. "<<sum<<" vs "<<run_avg.Average();
    }
    std::cout<<std::endl;
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
