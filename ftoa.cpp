#include "ftoa.h"
#include <cmath> // for frexp
#include <string.h> // for memmove

/* Doesn't check for memory length.
 * buf must be large enough to store 15 bytes
 */
const int maxp = 7; // max precision
char * ftoa( float x, char * buf, int width, int precision ){
  // Catch edge cases
  if( x == (1./0.)){
    strcpy(buf, "Inf");
    return buf + 3;
  } else if( x == (-1./0.)){
    strcpy(buf, "-Inf");
    return buf + 4;
  } else if( x == (0./0.)){
    strcpy(buf, "NaN");
    return buf + 3;
  } else if( x == 0. ){
    strcpy(buf, "0");
    return buf + 1;
  }
  // Validate the input
  if( width > maxp )
    width = maxp;
  if( width < 1 )
    width = 1;
  if( (precision+width) > maxp || precision < 0 )
    precision = maxp - width;
  // Get the magnitude
  int exp = simple_log10(x);
  if( exp < -30 ){
    x *= 1e30;
    x *= simple_pow10(-exp - 30 + maxp);
  } else {
    x *= simple_pow10(-exp + maxp);
  }
  // Convert the mantissa
  long repr = x;
  char * ptr = dtoa(repr, buf);
  //Put a decimal point in the right place
  int len = (ptr - buf) - width; // used for correcting exponent
  ptr = buf + width;
  if( '-' == *buf ){
    ++ptr;
    --len;
  }
  memmove(ptr+1, ptr, precision);
  *ptr++ = '.';
  // Truncate number to specified precision
  ptr += precision;
  //Append the exponent
  exp = exp + len - maxp;
  *ptr++ = 'e';
  ptr = dtoa(exp, ptr);
  return ptr;
}
  
// Only gives an approximate result
int simple_log10(float x){
  int exp;
  frexp(x, &exp);
  // Log10(2) = 0.30103
  float exp10 = exp * 0.30103;
  return exp10;
}

float simple_pow10(int exp){
  float y;
  if( exp < 0 ){
    exp += 38;
    y = 1e-38;
  } else {
    y = 1.;
  }
  /* Using a lookup-table per bit.
   * This should provide fast results while minimizing multiplies.
   */
  if( exp & 1 )
    y *= 1e1;
  if( exp & 2 )
    y *= 1e2;
  if( exp & 4 )
    y *= 1e4;
  if( exp & 8 )
    y *= 1e8;
  if( exp & 16 )
    y *= 1e16;
  if( exp & 32 )
    y *= 1e32;
  return y;
}

/* Helper function to avoid slow division */
char subn(long &x, long k){
  char a = '0';
  while( x >= k ){
    ++a;
    x -= k;
  }
  return a;
}

/* Helper function to determine magnitude of integer.
 * Could reformat this to be a binary search rather than linear search
 */
int log10_helper( long x ){
  if( x >= 1000000000 )
    return 9;
  if( x >= 100000000 )
    return 8;
  if( x >= 10000000 )
    return 7;
  if( x >= 1000000 )
    return 6;
  if( x >= 100000 )
    return 5;
  if( x >= 10000 )
    return 4;
  if( x >= 1000 )
    return 3;
  if( x >= 100 )
    return 2;
  if( x >= 10 )
    return 1;
  return 0;
}
 
char * dtoa( long x, char * buf ){
  char * ptr = buf;
  if( x < 0 ){
    *ptr++ = '-';
    x = -x;
  }
  int magnitude = log10_helper(x);
  // Effectively a GoTo statement
  // No breaks - execute through every subsequenty case
  switch(magnitude){
    case 9:
      *ptr++ = subn(x, 1000000000 );
    case 8:
      *ptr++ = subn(x, 100000000 );
    case 7:
      *ptr++ = subn(x, 10000000 );
    case 6:
      *ptr++ = subn(x, 1000000 );
    case 5:
      *ptr++ = subn(x, 100000 );
    case 4:
      *ptr++ = subn(x, 10000 );
    case 3:
      *ptr++ = subn(x, 1000 );
    case 2:
      *ptr++ = subn(x, 100 );
    case 1:
      *ptr++ = subn(x, 10 );
    case 0:
      *ptr++ = subn(x, 1 );
    default:
      *ptr = 0; // termination character
  }
  return ptr;
}
  
