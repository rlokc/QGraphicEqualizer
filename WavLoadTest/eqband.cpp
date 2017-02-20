#include "eqband.h"
#include <audioeffect.h>
#include <SDL_mixer.h>
#include <audioutils.h>
#include <Qt>
#include <cmath>
#include <deque>
#include <iterator>

//TODO: Make child classes for reverb, fir and vibratto seperately
EQBand::EQBand(float gain)
{
    this->gain = gain;
}

EQBand::EQBand()
{
    this->gain = 1.0f;
}

EQBand::~EQBand()
{

}

void EQBand::setCoeffs(float *coeffs)
{
    this->coeffs = coeffs;
}

std::deque<float> EQBand::callback(int chan, std::deque<float> stream)
{
    int len = stream.size();
    std::deque<float> outStream;

    //FIR-filter realisation
    for (int i=len-1; i>=0; i--)
    {
        float result = 0;
        //Convoluting current sample
        for (int k=0; k<FILTER_ORDER; k++)
        {
            if (i-k >= 0)
            {
                result += stream[i-k] * this->coeffs[k];
            } else {    //If sample is out of bounds of current chunk, pull it from the previous
                result += (float) previousChunk[FILTER_ORDER - (k-i)] * this->coeffs[k];
            }
        }
        result *= this->gain;
        outStream.push_front(result);
    }
    return outStream;
}

