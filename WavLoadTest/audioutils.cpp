#include "audioutils.h"
#include <string.h>
#include <eqband.h>
#include <mainwindow.h>
#include <iostream>
#include <deque>
#include <iterator>
#include <qtconcurrentrun.h>
#include <QVector>
#include <fft2dseries.h>

#define FFT_RESOLUTION 15


AudioEffect *rack[10];
short previousChunk[FILTER_ORDER];
short previousChunk_buf[FILTER_ORDER];
short filteredStream_arr[CHUNKSIZE*2];
short *filteredStream;

bool enaEQ = false;
bool enaReverb = false;
bool enaVibrato = false;
int fftInterval = 0;

QtCharts::QLineSeries *LineSeries[2];
int lineIndex = 0;


int LoadWavViaSDL(const char* filename)
{
    if (filename == ""){
        return NULL;
    }
    Mix_Chunk *wave = Mix_LoadWAV(filename);
    const char* error = Mix_GetError();
    qDebug() << "SDL_Mixer ERROR:" << error;
    int channel = Mix_PlayChannel(-1, wave, 0);
    error = Mix_GetError();
    qDebug() << "SDL_Mixer ERROR:" << error;
    //Initializing previous chunk to 0, used in filtering
    for (int i=0; i<128; i++)
    {
        previousChunk[i]=0;
    }
    //Init filtered stream
    for (int i=0; i<CHUNKSIZE*2; i++){
        filteredStream_arr[i] = 0;
    }
    filteredStream = filteredStream_arr;

    return channel;
}

int LoadWavViaSDL(const QString filename)
{
    const char* filename_new = QsToChar(filename);
    return LoadWavViaSDL(filename_new);
}

const char* QsToChar(QString a){
    return a.toUtf8().data();
}

void effectRack(int chan, void *stream, int len, void *udata)
{   


    //De-voiding stream pointer
    short* p_raw = (short*) stream;

    //Outputting unfiltered FFT if we hit the resolution
    if (fftInterval == FFT_RESOLUTION)
        performFFT(LineSeries[0], p_raw);

    std::deque<float> p(p_raw, p_raw + len/2);
    //Copying unfiltered last part of the chunk to use for next calculations
    short* lastChunkPtr = p_raw;     //redundant but w/e
    lastChunkPtr += (len/2-FILTER_ORDER);
    memcpy(&previousChunk_buf, lastChunkPtr, sizeof(short)*FILTER_ORDER);


//Filters
    if (enaEQ)
    {

        //Nulling filteredStream, filters will write into it
        for (int i=0; i<len/2; i++)
        {
            filteredStream[i] = 0;
        }

        QFuture<std::deque<float>> filtered[10];

        filtered[0] = QtConcurrent::run(callFilter0, chan, p);
        filtered[1] = QtConcurrent::run(callFilter1, chan, p);
        filtered[2] = QtConcurrent::run(callFilter2, chan, p);
        filtered[3] = QtConcurrent::run(callFilter3, chan, p);
        filtered[4] = QtConcurrent::run(callFilter4, chan, p);
        filtered[5] = QtConcurrent::run(callFilter5, chan, p);
        filtered[6] = QtConcurrent::run(callFilter6, chan, p);
        filtered[7] = QtConcurrent::run(callFilter7, chan, p);

        //replacing the stream with the sum of the futures
        std::deque<float> buf;
        buf.resize(p.size(), 0);
        for (int i=0; i<8; i++)
        {
            std::deque<float> filtResult = filtered[i].result();
            for (int j=0; j<len/2; j++)
            {
                buf[j] += (short) round(filtResult[j]);
            }
        }
        p = buf;
    }

        //After the chunk has been processed, switch lastChunk to the buffered one
        memcpy(&previousChunk, previousChunk_buf, sizeof(short)*FILTER_ORDER);

//Effects
    if (enaReverb)

    {
        p = rack[8]->callback(chan, p);
    }

    if (enaVibrato)
    {
        p = rack[9]->callback(chan, p);
    }

    for (int i=0; i<p.size(); i++)
    {
        filteredStream[i] = (short) round(p[i]);
    }
    //Replace the original stream with the filtered one
    memcpy(stream, filteredStream, len);

    //Outputting filtered FFT
    if (fftInterval == FFT_RESOLUTION)
    {
        performFFT(LineSeries[1], filteredStream);
        fftInterval = 0;
    }
    else
    {
        fftInterval++;
    }
}

//Dirty hacks to access member-functions.
//I'm sorry :((((((((((((((((((((((((((((
std::deque<float> callFilter0 (int chan, std::deque<float> stream)
{
    return rack[0]->callback(chan, stream);
}
std::deque<float> callFilter1(int chan, std::deque<float> stream)
{
    return rack[1]->callback(chan, stream);
}
std::deque<float> callFilter2(int chan, std::deque<float> stream)
{
    return rack[2]->callback(chan, stream);
}
std::deque<float> callFilter3(int chan, std::deque<float> stream)
{
    return rack[3]->callback(chan, stream);
}
std::deque<float> callFilter4(int chan, std::deque<float> stream)
{
    return rack[4]->callback(chan, stream);
}
std::deque<float> callFilter5(int chan, std::deque<float> stream)
{
    return rack[5]->callback(chan, stream);
}
std::deque<float> callFilter6(int chan, std::deque<float> stream)
{
    return rack[6]->callback(chan, stream);
}
std::deque<float> callFilter7(int chan, std::deque<float> stream)
{
    return rack[7]->callback(chan, stream);
}
