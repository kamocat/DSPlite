#ifndef DSPLITE_SOS_FILTER
#define DSPLITE_SOS_FILTER

#include <inttypes.h>

struct SOSystem{
    double b0;
    double b1;
    double b2;
    double a0;
    double a1;
    double a2;
};

/* cascaded Second Order System */
class SOSfilter{
public:
    SOSfilter(const struct SOSystem * coeffecients, uint8_t size);
    SOSfilter(const SOSfilter &copy);
    void Reset(double val);
    double Process(double sample);
    ~SOSfilter(void);
    friend class ZPK;
private:
    const struct SOSystem * h; // array of second-order coeffecients
    uint8_t len;
    double * x;
};

#endif
