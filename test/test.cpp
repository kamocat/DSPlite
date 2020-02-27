//test suite
#include "../src/DSPlite.h" 
#include "Filters.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <complex>

void TestSOS(void);
void TestIIR(void);

/** Zeros, poles, gain.

Except gain isn't included here. Oh well. */
class ZPK{
public:
  ZPK(const SOSfilter &sos);
  std::vector <std::complex <double>> zeros;
  std::vector <std::complex <double>> poles;
private:
  std::complex <double> root(double a, double b, double c);
};


std::complex <double> ZPK::root(double a, double b, double c){
  std::complex <double> k = b*b-4*a*c;
  k = std::sqrt(k) - b;
  k /= 2 * a;
  return( k );
}

ZPK::ZPK(const SOSfilter &coef){
  for( int i = 0; i < coef.len; ++i ){
    const struct SOSystem * sos = &(coef.h[i]);
    std::complex <double> z = root(sos->b0, sos->b1, sos->b2);
    zeros.push_back(z);
    std::complex <double> p = root(sos->a0, sos->a1, sos->a2);
    poles.push_back(p);
  }
}

void PlotZP(void);

int main( int argc, char ** argv){
    //TestSOS();
    TestIIR();
    //PlotZP();
    return 0;
}

void PlotZP(void){
    SOSfilter filter(example_elliptic, sizeof(example_elliptic));
    ZPK zp(filter);
    for( int i = 0; i < zp.poles.size(); ++i ){
      std::cout<<"w="<<std::arg(zp.poles[i])/3.141592<<"\u03C0" //pi char
      <<" r="<<std::abs(zp.poles[i])<<std::endl;
    }
}


void TestSOS(void){
    SOSfilter filter(example_elliptic, sizeof(example_elliptic));
    int size = 200;
    double val = 100;
    std::ofstream log;
    log.open("step.csv");
    filter.Reset(val);
    for( int i = 1; i < size; ++i){
        log<<filter.Process(val)<< std::endl;
    }
    log.close();
}

void TestIIR(void){
    IIRfilter filter(simple2, sizeof(simple2));
    int size = 200;
    double val = 100;
    std::ofstream log;
    log.open("step.csv");
    filter.Reset(val);
    for( int i = 1; i < size; ++i){
        log<<filter.Process(val)<< std::endl;
    }
    log.close();
}
