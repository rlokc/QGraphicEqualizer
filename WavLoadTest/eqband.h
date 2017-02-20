#ifndef EQBAND_H
#define EQBAND_H

#include <QObject>
#include <QtCore>
#include <deque>
#include <audioeffect.h>


class EQBand : public AudioEffect {
public:
    EQBand(float gain);
    EQBand();
    ~EQBand();

    using AudioEffect::callback;
    std::deque<float> callback(int chan, std::deque<float> stream) Q_DECL_OVERRIDE;
    void setCoeffs(float* coeffs);

//public slots:
//    void gainChanged(int vol);
};

#endif // EQBAND_H
