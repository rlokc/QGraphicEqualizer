#ifndef REVERBEFFECT_H
#define REVERBEFFECT_H

#include <audioeffect.h>
#include <combfilter.h>
#include <allpassfilter.h>

class ReverbEffect : public AudioEffect
{
public:
    ReverbEffect();
    using AudioEffect::callback;
    std::deque<float> callback(int chan, std::deque<float> stream) Q_DECL_OVERRIDE;

private:
    CombFilter *combFilters[4];
    AllPassFilter *allPass1;
    AllPassFilter *allPass2;

};

#endif // REVERBEFFECT_H
