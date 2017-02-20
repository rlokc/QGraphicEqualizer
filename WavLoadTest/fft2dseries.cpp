#include <fft2dseries.h>
#include <fftw3.h>
#include <QVector>
#include <QPointF>
#include <QDebug>
#include <math.h>

#define FREQUENCY 44100

int FFTsamples;
double *FFTin;
fftw_complex *FFTout;
fftw_plan FFTPlan;

QVector<QPointF> outPoints;


void initFFT(int n)
{
    FFTsamples = n;
    int inSize = sizeof(double) * n;
    FFTin  = (double*)       fftw_malloc(inSize);
    FFTout = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n/2);
    FFTPlan   = fftw_plan_dft_r2c_1d(n, FFTin, FFTout, FFTW_ESTIMATE);

    outPoints = QVector<QPointF>(n);
}

void performFFT(QtCharts::QLineSeries *series, short *data)
{
    for (int i=0; i<FFTsamples; i++){
        FFTin[i] = (double) data[i];
//        qDebug() << "In: " << data[i] << "=" << FFTin[i];
    }
    fftw_execute(FFTPlan);

    outPoints.clear();
    for(int i=0; i<FFTsamples/2; i++)
    {
        double outX = (double) FREQUENCY * i * 2 / FFTsamples;
        double outY = 2 * sqrt(FFTout[i][0]*FFTout[i][0] + FFTout[i][1]*FFTout[i][1]) / FFTsamples;
        //Transform to dB
        outY = 20*log10(outY);
//        qDebug() << outX << "; " << outY;
        outPoints.append(QPointF(outX, outY));
    }
    series->replace(outPoints);
//    qDebug() << "==========================================";
}

void closeFFT()
{
//    fftw_destroy_plan(FFTPlan);
//    fftw_free(FFTin);
//    fftw_free(FFTout);
}
