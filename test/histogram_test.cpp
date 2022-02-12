#include "../src/Histogram.h" 
#include <iostream>
int main( int argc, char ** argv)
{
    Histogram h(4);
    const int qty = 9;
    int x[qty] = {0,5,10,15,20,15,10,5,0};
    long a = 0;
    for(auto i=0; i < qty; ++i){
      a += x[i];
      h.Process(x[i]);
      h.Print();
    }
    a /= qty;
    std::cout<<"Mean: "<<a<<std::endl;
    std::cout<<"Median: "<<h.Median()<<std::endl;
    std::cout<<"Mode: "<<h.Mode()<<std::endl;
    std::cout<<"Standard Deviation: "<<h.StandardDeviation()<<std::endl;

    return 0;
}
