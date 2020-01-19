#include "SOS.h"

float kernel(float in, const struct SOSystem &coef, float * mem){
    in *= coef.a0;
    in -= mem[0] * coef.a1;
    in -= mem[1] * coef.a2;
    float out = in * coef.b0;
    out += mem[0] * coef.b1;
    out += mem[1] * coef.b2;
    mem[1] = mem[0];
    mem[0] = in;
    return out;
}

float SOSfilter::Process(float sample){
    float y = 1;
    for(int i = 0; i < len; ++i){
        y *= kernel(sample, h[i], x+i+i);
    }
    return y;
}

float SOSfilter::Stability(void){
    //FIXME: calculate stability
    return 1;
}

/** FIXME: I don't think this works properly */
void SOSfilter::Reset(float val=0.){
    float a = Stability();
    // Calculate the steady-state condition of a one-element feedback
    // steady = input + steady*(a) ===> steady = input / (1-a)
    val = val / (1-a);
    // Reset the internal state
    int len2 = len * 2;
    for(int i = 0; i < len2; ++i){
        x[i]=val;
    }
}

SOSfilter::SOSfilter(const struct SOSystem * coef, uint8_t size){
    len = size / (sizeof(struct SOSystem));
    h = coef;
    int len2 = len * 2;
    x = new float[len2];
    for(int i = 0; i < len2; ++i){
        x[i]=0;
    }
}

SOSfilter::SOSfilter(const SOSfilter &copy){
    len = copy.len;
    h = copy.h;
    int len2 = len * 2;
    x = new float[len2];
    for(int i = 0; i < len2; ++i){
        x[i]=0;
    }
}

SOSfilter::~SOSfilter(void){
    delete x;
    // Assume h is constant and doesn't need deletion
}
