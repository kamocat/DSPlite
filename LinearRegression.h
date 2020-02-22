#ifndef DSPLITE_LINEAR_REGRESSION
#define DSPLITE_LINEAR_REGRESSION

class Regression{
public:
    Regression(void);
    Regression(const Regression &copy);
    void Reset(void);
    void Append(double sample);
    double GetSlope(void);
    double GetOffset(void);
private:
    double slope, offset;
    double b0, b1;
    int n;
};

#endif
