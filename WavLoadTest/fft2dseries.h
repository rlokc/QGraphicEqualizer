#ifndef FFT2DSERIES_H
#define FFT2DSERIES_H

#include <QtCharts/QLineSeries>

void initFFT(int n);

void performFFT(QtCharts::QLineSeries *series, short *data);

void closeFFT();

#endif // FFT2DSERIES_H
