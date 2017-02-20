#include <SDL_mixer.h>
#include "audioeffect.h"
#include <audioutils.h>
#include <Qt>
#include <cmath>
#include <deque>
#include <iterator>
#include <ringbuffer.h>

//TODO: Make child classes for reverb, fir and vibratto seperately
AudioEffect::AudioEffect()
{

}

AudioEffect::~AudioEffect()
{
}


std::deque<float> callback(int chan, std::deque<float> stream){
    //Stub method
    //Should have been a virtual tbh
    std::deque<float> out(stream.begin(), stream.end());
    return out;
}

void AudioEffect::gainChanged(int valueint)
{
//    qDebug() << "DEBUG: Volume of effect changed";
    float value = valueint/100.0f;
    this->gain = value;
}
