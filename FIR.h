#ifndef DSPLITE_FIR_FILTER
#define DSPLITE_FIR_FILTER

#include <inttypes.h>

class FIRfilter{
public:
    FIRfilter(const double * coeffecients, uint8_t size);
    FIRfilter(const FIRfilter &copy);
    void Reset(double val);
    double Process(double sample);
    ~FIRfilter(void);
private:
    const double * h;
    uint8_t i, len;
    double * x;
};
#endif
