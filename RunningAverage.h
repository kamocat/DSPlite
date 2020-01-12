#ifndef DSPLITE_RUNNING_AVERAGE
#define DSPLITE_RUNNING_AVERAGE

#include "FIR.h"

class RunningAverage: public FIRfilter{
public:
    RunningAverage(int length);
    void Reset(void);
    float Append(float sample);
    float Average(void);
private:
    float sum;
};

#endif
