#-------------------------------------------------
#
# Project created by QtCreator 216-02-24T01:42:30
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent
#QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WavLoadTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    audioworker.cpp \
    audioutils.cpp \
    audioeffect.cpp \
#    fir_coeffs_512.cpp \
    fir_coeffs_128.cpp \
    eqband.cpp \
    reverbeffect.cpp \
    vibratoeffect.cpp \
    combfilter.cpp \
    allpassfilter.cpp \
    lfo.cpp \
    linegraphwidget.cpp \
    fft2dseries.cpp

HEADERS  += mainwindow.h\
    audioworker.h \
    audioutils.h \
    audioeffect.h \
    constants.h \
#    fir_coeffs_512.h \
    fir_coeffs_128.h \
    eqband.h \
    reverbeffect.h \
    vibratoeffect.h \
    ringbuffer.h \
    combfilter.h \
    allpassfilter.h \
    lfo.h \
    linegraphwidget.h \
    fft2dseries.h

#PRECOMPILED_HEADER = SDL2_Mixer.h

FORMS    += mainwindow.ui

##mac
#win32:CONFIG(release, debug|release): LIBS += -L$$/usr/lib/release/ -lSDL2_mixer
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/lib/debug/ -lSDL2_mixer
#else:unix: LIBS += -L/usr/local/lib -lSDL2_mixer\
#                    -L/usr/local/lib -lSDL2\


#INCLUDEPATH += /usr/local/include/SDL2/\


#linux
win32:CONFIG(release, debug|release): LIBS += -L$$/usr/lib/release/ -lSDL2_mixer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/lib/debug/ -lSDL2_mixer
else:unix: LIBS += -L/usr/lib/ -lSDL2_mixer\
                    -L/usr/lib/ -lSDL2\


INCLUDEPATH += /usr/include/SDL2/\

QMAKE_CXXFLAGS_DEBUG += -O3
QMAKE_CXXFLAGS_RELEASE += -O3

CONFIG += c++11

DISTFILES += \
    README

RESOURCES += \
    icons.qrc

unix|win32: LIBS += -lfftw3
