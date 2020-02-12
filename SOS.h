#ifndef DSPLITE_SOS_FILTER
#define DSPLITE_SOS_FILTER

#include <inttypes.h>

struct SOSystem{
    float b0;
    float b1;
    float b2;
    float a0;
    float a1;
    float a2;
};

/* cascaded Second Order System */
class SOSfilter{
public:
    SOSfilter(const struct SOSystem * coeffecients, uint8_t size);
    SOSfilter(const SOSfilter &copy);
    void Reset(float val);
    float Process(float sample);
    float Stability(void);
    ~SOSfilter(void);
    friend class ZPK;
private:
    const struct SOSystem * h; // array of second-order coeffecients
    uint8_t len;
    float * x;
};

#endif
