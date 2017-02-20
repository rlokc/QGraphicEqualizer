#include <audioworker.h>
#include <audioutils.h>
#include <eqband.h>
#include <vibratoeffect.h>
#include <reverbeffect.h>
#include <audioeffect.h>
#include <QDebug>
#include <QtCore>
#include <QBuffer>
#include <mainwindow.h>

AudioWorker::AudioWorker(QString fileName)
{
    this->fileName = fileName;
}

AudioWorker::~AudioWorker()
{
    qDebug("DEBUG:Thread stopped");
    //TODO: Thread cleanup
}

void AudioWorker::init()
{
    //If filename isn't specified, terminate
    if (this->fileName == "")
    {
        emit finished();
        return;
    }
    Mix_OpenAudio(SAMPLERATE, MIX_DEFAULT_FORMAT, 2, CHUNKSIZE);
    const char* error = Mix_GetError();
    qDebug() << "SDL_Mixer ERROR:" << error;
    int channel = LoadWavViaSDL(fileName);
    this->channel = channel;

    this->effectRack_init(channel);
    //effectRack is actually located in audioutils.cpp and calls callbacks of each effect in the rack
    Mix_RegisterEffect(this->channel, effectRack, NULL, NULL);

}

void AudioWorker::sliderChanged(int vol)
{
//    qDebug() << "DEBUG: sliderChanged slot fired";
    QString senderName_qs = sender()->objectName();
    int senderIndex = senderName_qs.right(1).toInt();   //Getting last character, which is an index of a bar
    switch (senderIndex)
    {
        case 0:
            emit changeGainFilt0(vol);
            break;
        case 1:
            emit changeGainFilt1(vol);
            break;
        case 2:
            emit changeGainFilt2(vol);
            break;
        case 3:
            emit changeGainFilt3(vol);
            break;
        case 4:
            emit changeGainFilt4(vol);
            break;
        case 5:
            emit changeGainFilt5(vol);
            break;
        case 6:
            emit changeGainFilt6(vol);
            break;
        case 7:
            emit changeGainFilt7(vol);
            break;
    }

}

void AudioWorker::toggleEQ(bool val)
{
    enaEQ = val;
}

void AudioWorker::toggleVibrato(bool val)
{
    enaVibrato = val;
}

void AudioWorker::toggleReverb(bool val)
{
    enaReverb = val;
}

//There must be a better way, don't want to repeat myself 8 times :(
void AudioWorker::effectRack_init(int channel){
    EQBand *eff0 = new EQBand();
    eff0->setCoeffs(filt0);
    connect(this, SIGNAL(changeGainFilt0(int)), eff0, SLOT(gainChanged(int)));
    rack[0] = eff0;

    EQBand *eff1 = new EQBand();
    eff1->setCoeffs(filt1);
    connect(this, SIGNAL(changeGainFilt1(int)), eff1, SLOT(gainChanged(int)));
    rack[1] = eff1;

    EQBand *eff2 = new EQBand();
    eff2->setCoeffs(filt2);
    connect(this, SIGNAL(changeGainFilt2(int)), eff2, SLOT(gainChanged(int)));
    rack[2] = eff2;

    EQBand *eff3 = new EQBand();
    eff3->setCoeffs(filt3);
    connect(this, SIGNAL(changeGainFilt3(int)), eff3, SLOT(gainChanged(int)));
    rack[3] = eff3;

    EQBand *eff4 = new EQBand();
    eff4->setCoeffs(filt4);
    connect(this, SIGNAL(changeGainFilt4(int)), eff4, SLOT(gainChanged(int)));
    rack[4] = eff4;

    EQBand *eff5 = new EQBand();
    eff5->setCoeffs(filt5);
    connect(this, SIGNAL(changeGainFilt5(int)), eff5, SLOT(gainChanged(int)));
    rack[5] = eff5;

    EQBand *eff6 = new EQBand();
    eff6->setCoeffs(filt6);
    connect(this, SIGNAL(changeGainFilt6(int)), eff6, SLOT(gainChanged(int)));
    rack[6] = eff6;

    EQBand *eff7 = new EQBand();
    eff7->setCoeffs(filt7);
    connect(this, SIGNAL(changeGainFilt7(int)), eff7, SLOT(gainChanged(int)));
    rack[7] = eff7;

    ReverbEffect *rvb = new ReverbEffect();
    rack[8] = rvb;

    VibratoEffect *vbr = new VibratoEffect();
    rack[9] = vbr;
}

