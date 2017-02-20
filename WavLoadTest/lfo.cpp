#include "lfo.h"
#include <constants.h>
#include <math.h>

LFO::LFO() : freq(0), phase(0)
{

}

float LFO::getValue()
{
    float value = sin(phase);
    phase += dp;

    while(phase > 2 * M_PI)
        phase -= 2*M_PI;

    return value;

}

void LFO::setFreq(float fr)
{
    freq = fr;
    //Recounting phase step
    dp = countDP(fr);
}

void LFO::setPhase(float ph)
{
    phase = ph;
}

float countDP(float freq)
{
    return 2 * M_PI * freq / SAMPLERATE;
}
