//test suite
#include "../LinearRegression.cpp"
#include "../IIR.h"
#include "../FIR.h"
#include "../Filters.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

void TestLinearRegression(void);
void TestIIR(void);
void TestFIR(void);

int main( int argc, char ** argv){
    //TestLinearRegression();
    //TestRunningAverage();
    TestIIR();
    return 0;
}

void TestIIR(void){
    IIRfilter filter(cheby1_100hz, sizeof(cheby1_100hz));
    int size = 20;
    std::ofstream log;
    log.open("impulse.csv");
    float y = filter.Process(100);// Impulse
    log<<y << std::endl; 
    for( int i = 1; i < size; ++i){
        y = filter.Process(0);
        log<<y<< std::endl;
    }
    log.close();
}

void TestFIR(void){
    FIRfilter filter(exp_decay, sizeof(exp_decay));
    int size = 20;
    std::ofstream log;
    log.open("impulse.csv");
    log<<filter.Process(100) << std::endl; // Impulse
    for( int i = 1; i < size; ++i){
        log<<filter.Process(0) << std::endl;
    }
    log.close();
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
