#include "reverbeffect.h"
#include <constants.h>
#include <math.h>

ReverbEffect::ReverbEffect()
{
    int len[4];
    len[0] = (int) 29.7*44.1;   //29.7 miliseconds
    len[1] = (int) 37.1*44.1;
    len[2] = (int) 41.1*44.1;
    len[3] = (int) 43.7*44.1;
    combFilters[0] = new CombFilter(29.7 * 44.1);
    combFilters[1] = new CombFilter(37.1 * 44.1);
    combFilters[2] = new CombFilter(41.1 * 44.1);
    combFilters[3] = new CombFilter(43.7 * 44.1);
    allPass1 = new AllPassFilter(20.0 * 44.1, pow(0.001, 20.0/96.83));
    allPass2 = new AllPassFilter(40.0 * 44.1, pow(0.001, 40.0/32.92));
}


std::deque<float> ReverbEffect::callback(int chan, std::deque<float> stream)
{
    std::deque<float> out[4];
    std::deque<float> outStream;
    outStream.resize(stream.size(), 0);

    for (int i = 0; i<4; i++)
    {
        out[i] = combFilters[i]->filter(stream);
        for (int j=0; j<out[i].size(); j++)
        {
           outStream[j] += (out[i][j])/4;
        }
    }

    outStream = allPass1->filter(outStream);
    outStream = allPass2->filter(outStream);

    return outStream;

}


