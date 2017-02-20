#ifndef AUDIOWORKER_H
#define AUDIOWORKER_H

#include <QObject>
#include <QString>
#include <audioutils.h>
#include <audioeffect.h>
#include <fir_coeffs_128.h>
#include <constants.h>

class AudioWorker : public QObject
{
    Q_OBJECT
public:
    AudioWorker(QString fileName);
    ~AudioWorker();
    void addEffect(AudioEffect *effect);
    void effectRack_init(int channel);

public slots:
    void init();
    void sliderChanged(int vol);
    void toggleEQ(bool val);
    void toggleVibrato(bool val);
    void toggleReverb(bool val);

signals:
    void finished();
    void error(QString err);
    void changeFilterVolume(int vol);
    void changeGainFilt0(int vol);
    void changeGainFilt1(int vol);
    void changeGainFilt2(int vol);
    void changeGainFilt3(int vol);
    void changeGainFilt4(int vol);
    void changeGainFilt5(int vol);
    void changeGainFilt6(int vol);
    void changeGainFilt7(int vol);

private:
    QString fileName;
    int channel;
};


#endif // AUDIOWORKER_H
