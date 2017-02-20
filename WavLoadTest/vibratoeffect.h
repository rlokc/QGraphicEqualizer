#ifndef VIBRATOEFFECT_H
#define VIBRATOEFFECT_H

#include <audioeffect.h>
#include <lfo.h>
#include <deque>

class VibratoEffect : public AudioEffect
{
public:
    VibratoEffect();
    using AudioEffect::callback;
    std::deque<float> callback(int chan, std::deque<float> stream) Q_DECL_OVERRIDE;

private:
    float freq;
    float depth;
    LFO *lfo;
    std::deque<float> delayBuffer;
};

#endif // VIBRATOEFFECT_H
