#include "../src/Histogram.h" 
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

void test_sorting(void){
    Histogram h(100);
    for(auto j=2; j<32; ++j){
        h.Reset();
        for(auto i=j; i; --i){
            h.Process(i);
        }
        h.Sort();
        if(!h.Sorted()){
            std::cout<<"Failed to sort list of qty "<<j<<" :\n";
            h.Print();
        }
    }
}

void test_rebalance(void){
    Histogram h(4);
    const int qty = 9;
    int x[qty] = {0,5,10,15,20,15,10,5,0};
    long a = 0;
    for(auto i=0; i < qty; ++i){
      a += x[i];
      h.Process(x[i]);
      h.Print();
      std::cout<<"Median: "<<h.Median()<<std::endl;
    }
    a /= qty;
    std::cout<<"Mean: "<<a<<std::endl;
    std::cout<<"Median: "<<h.Median()<<std::endl;
    std::cout<<"Mode: "<<h.Mode()<<std::endl;
    std::cout<<"Standard Deviation: "<<sqrt(h.Variance())<<std::endl;
}

void test_shape(void){
    std::random_device rd{};
    std::mt19937 gen{rd()};
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{50,20};
    Histogram h(100);
    long long a = 0;
    int qty = 155;
    for(auto i=0; i < qty; ++i){
      int x = std::round(d(gen));
      a += x;
      h.Process(x);
    }
    //h.Print();
    a /= qty;
    std::cout<<"Mean: "<<a<<std::endl;
    std::cout<<"Median: "<<h.Median()<<std::endl;
    std::cout<<"Mode: "<<h.Mode()<<std::endl;
    std::cout<<"Standard Deviation: "<<sqrt(h.Variance())<<std::endl;
}

void test_convergence_rate(void){
    std::ofstream log;
    log.open("converge.csv");
    std::random_device rd{};
    std::mt19937 gen{rd()};
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d{100,100};
    Histogram h(100);
    long long a = 0;
    int qty = 1000;
    double y = 0;
    log<<"iteration mean median filtered"<<std::endl;
    for(auto i=0; i < qty; ++i){
      int x = std::round(d(gen));
      h.Process(x);
      y += (x-y)*0.005; // First-order lowpass filter
      if(i>5){
        log<<i<<", "<<h.Mean()<<", "<<h.Median()<<", "<<y<<std::endl;
      }
    }
    log.close();
}


int main( int argc, char ** argv)
{

    test_sorting();
    test_shape();
    test_convergence_rate();
    return 0;
}
