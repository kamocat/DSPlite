#include "../src/Histogram.h" 
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cmath>
int main( int argc, char ** argv)
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{50,20};
    Histogram h(200);
    long long a = 0;
    int qty = 1000;
    for(auto i=0; i < qty; ++i){
      int x = std::round(d(gen));
      a += x;
      h.Process(x);
    }
    a /= qty;
    std::cout<<"Mean: "<<a<<std::endl;
    std::cout<<"Median: "<<h.Median()<<std::endl;
    std::cout<<"Mode: "<<h.Mode()<<std::endl;
    std::cout<<"Standard Deviation: "<<h.StandardDeviation()<<std::endl;

    return 0;
}
