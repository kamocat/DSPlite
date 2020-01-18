#ifndef DSPLITE_IIR_FILTER
#define DSPLITE_IIR_FILTER

#include <inttypes.h>

class IIRfilter{
public:
    IIRfilter(const float * coeffecients, uint8_t size);
    IIRfilter(const IIRfilter &copy);
    void Reset(float val);
    float Process(float sample);
    float Stability(void);
    ~IIRfilter(void);
private:
    const float * h; // Interlieved numerator/denominator coeffecients
    uint8_t i, len;
    float * x;
};

#endif
