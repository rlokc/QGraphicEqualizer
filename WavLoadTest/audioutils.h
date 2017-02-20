#ifndef SOUNDLIB_H
#define SOUNDLIB_H

#include "SDL_mixer.h"
#include "SDL.h"
#include <QString>
#include <audioeffect.h>
#include <eqband.h>
#include <constants.h>
#include <QtCharts/QLineSeries>


int LoadWavViaSDL(const char* filename);
int LoadWavViaSDL(const QString filename);
void testEffect(int chan, void *stream, int len, void *udata);
const char* QsToChar(QString a);

//void effectRack_init(int channel);
void effectRack(int chan, void *stream, int len, void *udata);

extern AudioEffect *rack[10];
extern short previousChunk[FILTER_ORDER]; //Previous processed chunk, fixes crackles.
extern bool enaEQ;
extern bool enaVibrato;
extern bool enaReverb;
extern QtCharts::QLineSeries *LineSeries[2];
extern int lineIndex;

//Maybe make it dependent on filter order actually

std::deque<float> callFilter0 (int chan, std::deque<float> stream);
std::deque<float> callFilter1 (int chan, std::deque<float> stream);
std::deque<float> callFilter2 (int chan, std::deque<float> stream);
std::deque<float> callFilter3 (int chan, std::deque<float> stream);
std::deque<float> callFilter4 (int chan, std::deque<float> stream);
std::deque<float> callFilter5 (int chan, std::deque<float> stream);
std::deque<float> callFilter6 (int chan, std::deque<float> stream);
std::deque<float> callFilter7 (int chan, std::deque<float> stream);

#endif // SOUNDLIB_H
