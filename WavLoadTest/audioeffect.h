#ifndef AUDIOEFFECT_H
#define AUDIOEFFECT_H

#include <QtCore>
#include <deque>

class AudioEffect: public QObject
{
    Q_OBJECT
public:
    AudioEffect();
    ~AudioEffect();
//    void callback(int chan, short *stream, int len, void *udata, short *outStream);
    //Pure virtual function
    virtual std::deque<float> callback(int chan, std::deque<float> stream) = 0;

public slots:
    void gainChanged(int vol);      //Dirty hack. For some reason, can't have both virtual methods and slots at the same time in a derived class

protected:
    int channel;
    float *coeffs;
    float gain;
    float decay;
    float length;
    std::deque<float> delayBuffer;
};

#endif // AUDIOEFFECT_H
