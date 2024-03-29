#ifndef DSPLITE_HISTOGRAM
#define DSPLITE_HISTOGRAM

#include <inttypes.h>


class Histogram{
public:
    Histogram(uint16_t size);
    Histogram(const Histogram &copy);
    void Reset(void);
    void Process(int16_t sample);
    int32_t Variance(void);
    int16_t Mode(void);
    int16_t Median(void);
    int16_t Mean(void);
    void Print(void);
    void Sort(void);
    bool Sorted(void);
    ~Histogram(void);
private:
    int16_t offset;
    uint16_t size;
    uint16_t count;
    int16_t * bin;
    int32_t sum;
};

#endif
