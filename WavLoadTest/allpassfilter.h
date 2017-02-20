#ifndef ALLPASSFILTER_H
#define ALLPASSFILTER_H

#include<deque>

#include <deque>
class AllPassFilter
{
public:
    AllPassFilter(float length, float decay);
    ~AllPassFilter();
    std::deque<float> filter(std::deque<float> &in);
    void resize (float length);
    float decay;

private:
    std::deque<float> delayBuffer;
    int bufferLength;
};

#endif // ALLPASSFILTER_H
