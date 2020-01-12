#ifndef DSPLITE_LINEAR_REGRESSION
#define DSPLITE_LINEAR_REGRESSION

class Regression{
public:
    Regression(void);
    Regression(const Regression &copy);
    void Reset(void);
    void Append(float sample);
    float GetSlope(void);
    float GetOffset(void);
private:
    float slope, offset;
    float b0, b1;
    int n;
};

#endif
