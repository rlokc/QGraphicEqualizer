#include "allpassfilter.h"
#include <math.h>


AllPassFilter::AllPassFilter(float length, float dec)
{
    bufferLength = (int) length;
    delayBuffer.resize(bufferLength, 0);
//    decay = 0.85;
//    decay = pow(0.001, bufferLength/44.1/1000);
    decay = dec;

//    decay = 0.0010715193052376064;
}

std::deque<float> AllPassFilter::filter(std::deque<float> &in)
{
    std::deque<float> out;
    out.resize(in.size(),0);

    for (int i=0; i < in.size(); i++)
    {
        out[i] = in[i] - delayBuffer.front() * decay;

        delayBuffer.push_back(in[i] + delayBuffer.front() * decay);
        delayBuffer.pop_front();

    }

    return out;
}

void AllPassFilter::resize (float length)
{
    bufferLength = (int) length;
    delayBuffer.resize(bufferLength, 0);
}
