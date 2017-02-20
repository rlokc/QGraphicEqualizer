#ifndef COMBFILTER_H
#define COMBFILTER_H

#include <deque>
class CombFilter
{
public:
    CombFilter(int length);
    ~CombFilter();
    std::deque<float> filter(std::deque<float> &in);
    void resize (int length);
    float decay;

private:
    std::deque<float> delayBuffer;
    int bufferLength;
};
#endif // COMBFILTER_H
