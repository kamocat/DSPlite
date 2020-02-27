#ifndef DSPLITE_IIR_FILTER
#define DSPLITE_IIR_FILTER

#include <inttypes.h>

class IIRfilter{
public:
    IIRfilter(const double * coeffecients, uint8_t size);
    IIRfilter(const IIRfilter &copy);
    void Reset(double val);
    double Process(double sample);
    ~IIRfilter(void);
private:
    const double * h; // Interlieved numerator/denominator coeffecients
    uint8_t i, len;
    double * x;
};

#endif
