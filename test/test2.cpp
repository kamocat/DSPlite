#include "../ftoa.h"
#include <iostream>

void test_ftoa( float x ){
  char buf[15];
  ftoa(buf, x, 5);
  std::cout<<x<<" vs "<<buf<<std::endl;
}
  

int main( int argc, char ** argv ){
  float pi = 3.141592;
  float m;
  for(m = 1; m > 0.; m/=10){
    test_ftoa( m * pi );
  }
  for(m = 1; m < 2e38; m*=10){
    test_ftoa( m * pi );
  }
}
