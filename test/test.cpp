//test suite
#include "../src/SOS.h" 
#include "Filters.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <complex>

void TestSOS(void);

int main( int argc, char ** argv){
    TestSOS();
    //TestIIR();
    //PlotZP();
    return 0;
}


void TestSOS(void){
    struct SOSfilter filter;
    SOSInit(&filter, example_elliptic, sizeof(example_elliptic));
    int size = 200;
    double val = 100;
    std::ofstream log;
    log.open("step.csv");
    SOSReset(&filter, 0);
    for( int i = 1; i < size; ++i){
        log<<SOSProcess(&filter, val)<< std::endl;
    }
    log.close();
    SOSDelete(&filter);
}
