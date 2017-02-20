#include "linegraphwidget.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QVBoxLayout>
#include <audioutils.h>

QT_CHARTS_USE_NAMESPACE

LineGraphWidget::LineGraphWidget(QWidget *parent) : QWidget(parent)
{
        QChart *m_chart = new QChart;
        QChartView *chartView = new QChartView(m_chart);
        m_chart->setTheme(QChart::ChartThemeDark);

//        chartView->setMinimumSize(800, 600);
        QLineSeries *m_series = new QLineSeries;
        m_chart->addSeries(m_series);
        LineSeries[lineIndex] = m_series;
        lineIndex++;

        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(0, 22050);
//        axisX->setLabelFormat("%g");
//        axisX->setTitleText("Samples");
        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(0, 80);
//        axisY->setTitleText("Audio level");
        m_chart->setAxisX(axisX, m_series);
        m_chart->setAxisY(axisY, m_series);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(chartView);
        setLayout(mainLayout);
}
