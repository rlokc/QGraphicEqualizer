#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QThread>
#include <QtCharts>
#include <fft2dseries.h>

#include <audioworker.h>
//#include <audioeffect.h>
#include "audioutils.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    closeFFT();
    event->accept();
}

void MainWindow::errorString(QString error)
{
    qDebug() << "Error recieved from thread:" << error;
}

void MainWindow::on_actionOpen_triggered()
{
    const QString defPath = "/Users/rlokc/Dropbox/Education/6 sem/courseworks/nedash/qt tests";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Kek"), defPath, tr("Music files (*.wav *.mp3 *.flac)"));
    ui->textBrowser->setText(fileName);

    initAudio(fileName);
}

void MainWindow::initAudio(QString fileName)
{
    initFFT(CHUNKSIZE);
    QThread *thread = new QThread;
    AudioWorker *worker = new AudioWorker(fileName);
    worker->moveToThread(thread);
    connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(init()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(ui->slider_filt0,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt1,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt2,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt3,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt4,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt5,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt6,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->slider_filt7,     SIGNAL(valueChanged(int)), worker, SLOT(sliderChanged(int)));
    connect(ui->BtnToggleEQ,      SIGNAL(toggled(bool))    , worker, SLOT(toggleEQ(bool)));
    connect(ui->BtnToggleReverb,  SIGNAL(toggled(bool))    , worker, SLOT(toggleReverb(bool)));
    connect(ui->BtnToggleVibrato, SIGNAL(toggled(bool))    , worker, SLOT(toggleVibrato(bool)));
    thread->start();
    thread->setPriority(QThread::HighPriority);

    initGraphs();
}

void MainWindow::initGraphs()
{
    QChart *chart = new QChart;
    QChartView *view = new QChartView(chart);
    view->setMinimumSize(800, 600);
    QLineSeries *ser = new QLineSeries;
    chart->addSeries(ser);

}


void MainWindow::on_btnDebug_clicked()
{

    qDebug() << "Debug started";
    return;

}
