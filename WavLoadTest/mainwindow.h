#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int slider1;

private slots:
    void on_actionOpen_triggered();

    void on_btnDebug_clicked();

public slots:
    void errorString(QString);

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    void initAudio(QString fileName);
    void initGraphs();
};

#endif // MAINWINDOW_H
