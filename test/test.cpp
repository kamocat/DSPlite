//test suite
#include "../DSPlite.h"
#include "Filters.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <complex>

void TestSOS(void);

/** Zeros, poles, gain.

Except gain isn't included here. Oh well. */
class ZPK{
public:
  ZPK(const SOSfilter &sos);
  std::vector <std::complex <float>> zeros;
  std::vector <std::complex <float>> poles;
private:
  std::complex <float> root(float a, float b, float c);
};


std::complex <float> ZPK::root(float a, float b, float c){
  std::complex <float> k = b*b-4*a*c;
  k = std::sqrt(k) - b;
  k /= 2 * a;
  return( k );
}

ZPK::ZPK(const SOSfilter &coef){
  for( int i = 0; i < coef.len; ++i ){
    const struct SOSystem * sos = &(coef.h[i]);
    std::complex <float> z = root(sos->b0, sos->b1, sos->b2);
    zeros.push_back(z);
    std::complex <float> p = root(sos->a0, sos->a1, sos->a2);
    poles.push_back(p);
  }
}

void PlotZP(void);

int main( int argc, char ** argv){
    //TestSOS();
    PlotZP();
    return 0;
}

void PlotZP(void){
    SOSfilter filter(cheby1_10hz, sizeof(cheby1_10hz));
    ZPK zp(filter);
    for( int i = 0; i < zp.poles.size(); ++i ){
      std::cout<<"w="<<std::arg(zp.poles[i])/3.141592<<"\u03C0" //pi char
      <<" r="<<std::abs(zp.poles[i])<<std::endl;
    }
}


void TestSOS(void){
    SOSfilter filter(butter_10hz, sizeof(butter_10hz));
    int size = 2000;
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
