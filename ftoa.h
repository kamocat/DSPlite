#ifndef DSPLITE_FTOA
#define DSPLITE_FTOA

/* Converts a float to a character array.
 * Doesn't handle INF, -INF, or NaN.
 * Works on subnormal numbers
 * Assumes buf can store at least 15 bytes
 * Returns pointer to end of array
 */
char * ftoa( float x, char * buf, int whole=1, int precision=5);

/* Converts a long integer to a character array
 * Doesn't correctly handle LONG_MIN (0x80000000)
 * Assumes buf can store 12 bytes
 * Returns pointer to end of the array
 */ 
char * dtoa( long x, char * buf );

// Gives any integer power of 10 from -127 to 127
float simple_pow10(int exp);

// Gives approximate log-10 of a float
int simple_log10(float x);

#endif
