#ifndef DSPLITE_SOS_FILTER
#define DSPLITE_SOS_FILTER

#include <inttypes.h>

/* cascaded Second Order System */
struct SOSystem{
    double b0;
    double b1;
    double b2;
    double a0;
    double a1;
    double a2;
};

struct SOSfilter{
    const struct SOSystem * h; // array of second-order coeffecients
    uint8_t len;
    double * x;
};

void SOSInit(struct SOSfilter * s, const struct SOSystem * coeffecients, uint8_t size);

void SOSReset(struct SOSfilter * s, double val);

double SOSProcess(struct SOSfilter * s, double sample);

void SOSDelete(struct SOSfilter * s);

#endif
