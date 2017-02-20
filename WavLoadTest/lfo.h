#ifndef LFO_H
#define LFO_H


class LFO
{
public:
    LFO();
    float getValue();
    void setFreq(float fr);
    void setPhase(float ph);

private:
    float phase;
    float dp;
    float freq;
};

float countDP(float freq);

#endif // LFO_H
