#include "vibratoeffect.h"
#include <constants.h>
#include <cmath>
#include <QDebug>

VibratoEffect::VibratoEffect()
{
    lfo = new LFO();
    lfo->setFreq(5);
    delayBuffer.resize((int) 44100*0.05, 0);  //Delay time - 0.05s
    depth = 0.1;
}

std::deque<float> VibratoEffect::callback(int chan, std::deque<float> stream)
{
    float delayTime = 0.05;
    std::deque<float> outStream;
    outStream.resize(stream.size(), 0);
//    qDebug() << "Buffer size: " << delayBuffer.size();
//    qDebug() << "Stream chunk size: " << stream.size();

    for (int i = 0; i < stream.size(); i++)
    {
        //readPos of the delay buffer is modulated by an LFO
        float lfoVal = lfo->getValue();
//        qDebug() << "i: " << i;
//        qDebug() << "lfo: " << lfoVal;
        int readPos = (int) i + round((delayTime/2 * (1 +lfoVal * depth)) * SAMPLERATE);
//        qDebug() << "readPos: " << readPos;
        if(readPos > delayBuffer.size()) readPos = delayBuffer.size();
        if(readPos < 0) readPos = 0;


        outStream[i] = delayBuffer[readPos];
    }

    //Replacing the samples in the delay buffer with the new ones
    for (int i = 0; i < stream.size(); i++)
    {
        delayBuffer.pop_front();
        delayBuffer.push_back(stream[i]);
    }

    return outStream;
}
