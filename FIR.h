#ifndef DSPLITE_FIR_FILTER
#define DSPLITE_FIR_FILTER

// Finite Impulse Response filter template

class FIRfilter{
public:
    FIRfilter(int length);
    // No copy constructor - it would duplicate the allocated memory
    void Reset(void);
    float Convolve(float * h, int len);
    void Append(float sample);
    ~FIRfilter(void);
protected:
    float * data;
    int i, len, maxlen, mask;
};

#endif
