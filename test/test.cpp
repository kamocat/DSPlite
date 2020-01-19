//test suite
#include "../DSPlite.h"
#include "Filters.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

void TestSOS(void);

int main( int argc, char ** argv){
    TestSOS();
    return 0;
}

void TestSOS(void){
    SOSfilter filter(butter_50hz, sizeof(butter_50hz));
    int size = 200;
    float val = 100;
    std::ofstream log;
    log.open("step.csv");
    for( int i = 1; i < size; ++i){
        log<<filter.Process(val)<< std::endl;
    }
    log.close();
    float n = 5;
    filter.Reset(5);
    std::cout<<"Reset to "<<n<<std::endl<<"Results: ";
    for( int i = 0; i < 3; ++i ){
        std::cout<<filter.Process(n)<<" ";
    }
    std::cout<<std::endl;
}
