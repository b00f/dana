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

#include "reportdialog.h"
#include "constants.h"
#include "deck.h"

#include <QtCharts/QPieSeries>

ReportDialog::ReportDialog(QWidget *parent)
    : QxDialog("report_dialog", parent)
{
    setupView();

    setWindowTitle(STR_DIALOG_TITLE_REPORT);
}

void ReportDialog::setupModel(Deck *deck)
{
    QPieSeries *series = new QPieSeries();

    for(int i=0;i<LevelCount+1;i++)
    {
        series->append(LevelsName[i],
                       deck->getCardsNo(i));

        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setLabelColor(LevelsColor[i]);
        slice->setPen(QPen(Qt::white, 1));
        slice->setBrush(LevelsColor[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGridLayout *mainLayout = new QGridLayout(this);

    mainLayout->addWidget(chartView);
}

void ReportDialog::setupView()
{
}
