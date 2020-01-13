#ifndef DSPLITE_FIR_FILTER
#define DSPLITE_FIR_FILTER

#include <inttypes.h>

class FIRfilter{
public:
    FIRfilter(const float * coeffecients, uint8_t size);
    FIRfilter(const FIRfilter &copy);
    void Reset(float val);
    float Process(float sample);
    ~FIRfilter(void);
private:
    const float * h;
    uint8_t i, len;
    float * x;
};
#endif
