//
// Dana - Dana, Symbol of Wisdom
// Copyright (C) 2014 Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
//
// This file is part of Dana.
//
// Dana is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dana is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dana.  If not, see <http://www.gnu.org/licenses/>.
//

#include "histograph.h"
#include "constants.h"

#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QGraphicsLayout>

Histograph::Histograph(QWidget *parent)
    : QtCharts::QChartView(parent)
{
}

void Histograph::setHistory(CardHistory* history, bool embeded)
{
    QList<Point*> points = history->getPoints();

    QtCharts::QScatterSeries *series0 = new QtCharts::QScatterSeries(this);
    QtCharts::QLineSeries *series1 = new QtCharts::QLineSeries(this);

    for (auto it=points.constBegin();
        it!=points.constEnd(); ++it) {

        series0->append((*it)->time.toMSecsSinceEpoch(), (*it)->level);
        series1->append((*it)->time.toMSecsSinceEpoch(), (*it)->level);
    }
    series0->setMarkerShape(QtCharts::QScatterSeries::MarkerShapeRectangle);
    series0->setMarkerSize(8);

    /// fix a bug in qtchart. when there is just one point, it doesn't show anything.
    if(series0->count()==1) {
        series0->append(points[0]->time.toMSecsSinceEpoch()+100, points[0]->level);
        series1->append(points[0]->time.toMSecsSinceEpoch()+100, points[0]->level);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->legend()->hide();
    chart->addSeries(series0);
    chart->addSeries(series1);
    chart->setMargins(QMargins(4,4,4,4));
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    setRenderHint(QPainter::Antialiasing);

    QtCharts::QDateTimeAxis *axisX = new QtCharts::QDateTimeAxis;

    axisX->setFormat("dd MMM");
    //axisX->setTitleText("Date");
    axisX->setTickCount(1);
    chart->addAxis(axisX, Qt::AlignBottom);
    series0->attachAxis(axisX);
    series1->attachAxis(axisX);

    QtCharts::QCategoryAxis *axisY = new QtCharts::QCategoryAxis;
    //axisY->setTitleText("Level");
    axisY->setRange(Level_1, Level_Retired);
    axisY->setStartValue(Level_1);
    axisY->append("1", Level_1);
    axisY->append("2", Level_2);
    axisY->append("3", Level_3);
    axisY->append("4", Level_4);
    axisY->append("5", Level_5);
    axisY->append("R", Level_Retired);
    axisY->setLabelsVisible(false);
    axisY->setLabelsPosition(QtCharts::QCategoryAxis::AxisLabelsPositionCenter);
    axisY->setTickCount(1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series0->attachAxis(axisY);
    series1->attachAxis(axisY);

    if(embeded) {
        axisX->setLabelsVisible(false);
        chart->setBackgroundVisible(false);
        chart->setMargins(QMargins(-20,-8,-8,-20));
        series0->setMarkerSize(4);
    }

    setChart(chart);
}
