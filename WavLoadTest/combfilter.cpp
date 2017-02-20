#include "combfilter.h"
#include <math.h>


CombFilter::CombFilter(int length)
{
    bufferLength = length;
    delayBuffer.resize(length, 0);
    decay = pow(0.001, bufferLength/44.1/1000);

}

std::deque<float> CombFilter::filter(std::deque<float> &in)
{
    std::deque<float> out;
    out.resize(in.size(),0);

    for (int i=0; i < in.size(); i++)
    {
        out [i] = delayBuffer.front();

        delayBuffer.pop_front();
        delayBuffer.push_back(in[i] + delayBuffer.front()*decay);
    }

    return out;
}

void CombFilter::resize (int length)
{
    bufferLength = length;
    delayBuffer.resize(length, 0);
}
