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
#include "pieview.h"
#include "deck.h"


ReportDialog::ReportDialog(QWidget *parent)
    : QxDialog("report_dialog", parent)
{
    model = new QStandardItemModel(8, 2, this);

	model->setHeaderData(0, Qt::Horizontal, STR_REPORT_HEADER_LEVEL);
    model->setHeaderData(1, Qt::Horizontal, STR_REPORT_HEADER_COUNT);
	
	setupView();

    setWindowTitle(STR_DIALOG_TITLE_REPORT);
}

void ReportDialog::setupModel(Deck *deck)
{
    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());

    int row = 0;
    int count = 0;
    for(int i=0;i<LevelCount+1;i++)
	{
        count = deck->getCardsNo(i);
        QVariant color = LevelsColor[i];

        model->insertRows(row, 1, QModelIndex());

        model->setData(model->index(row, 0, QModelIndex()),
            LevelsName[i]);
        model->setData(model->index(row, 1, QModelIndex()),
            QString("%1").arg(count));
        model->setData(model->index(row, 0, QModelIndex()),
            color, Qt::DecorationRole);
		row++;
	}
}

void ReportDialog::setupView()
{
    QGridLayout *mainLayout = new QGridLayout(this);
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
	QTableView *table = new QTableView;
	pieChart = new PieView;
	splitter->addWidget(table);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

	table->setModel(model);
	pieChart->setModel(model);

	QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
	table->setSelectionModel(selectionModel);
	pieChart->setSelectionModel(selectionModel);

    table->verticalHeader()->setVisible(false);

	QHeaderView *headerView = table->horizontalHeader();
	headerView->setStretchLastSection(true);

    mainLayout->addWidget(splitter);
}
