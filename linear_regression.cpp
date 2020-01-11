#include "linear_regression.h"

void Regression::Reset(void){
    slope = 0;
    offset = 0;
    n = 0;
    b0 = 0;
    b1 = 0;
}

Regression::Regression(void){
    Reset();
}

Regression::Regression(const Regression &copy){
    slope = copy.slope;
    offset = copy.offset;
    n = copy.n;
    b0 = copy.b0;
    b1 = copy.b1;
}

void Regression::Append(float sample){
    b0 += sample;
    b1 += sample * n;
    ++n;
}

float Regression::GetSlope(void){
    // Solve using the closed-form solution of linear regression
    // First: Make a 2x2 matrix
    float a[4];
    a[0] = n;
    a[1] = a[0] * (a[0]-1) * 0.5; // sum of 1:n
    a[2] = a[1];
    a[3] = a[1] * (a[0]-0.5) * (2./3.); // sum of squares of 1:n
    // Second: Invert the matrix
    float det = 1. / (a[0]*a[3] - a[1]*a[1]);
    a[2] = a[3] * det; // using a[2] as tmp
    a[3] = a[0] * det;
    a[0] = a[2]; // done using as tmp
    a[1] = a[1] * (-det); 
    a[2] = a[1];
    // Third: dot product of a and b
    offset = a[0]*b0 + a[2]*b1;
    slope = a[1]*b0 + a[3]*b1;
    return slope;
}

float Regression::GetOffset(void){
    // Assume you already called slope()
    return offset;
}
