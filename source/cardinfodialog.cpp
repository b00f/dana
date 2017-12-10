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

#include "cardinfodialog.h"
#include "constants.h"

#define SETTING_HISTORY_COLUMN_TIME    "history_column_time"
#define SETTING_HISTORY_COLUMN_LEVEL   "history_column_level"

CardInfoDialog::CardInfoDialog(QWidget *parent)
    : QxDialog("card_info_dialog", parent)
{
    setupView();
}

void CardInfoDialog::setupView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *headerLayout = new QHBoxLayout;
    QVBoxLayout *historyLayout = new QVBoxLayout;

    tableHistory = new QTableView(this);
    lableHistory = new QLabel(STR_CARD_HISTORY, this);
    histograph =  new Histograph(this);

    histograph->setToolTip(STR_QUERY_HISTOGRAPH_TIP);
    histograph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    histograph->setFixedHeight(200);

    historyLayout->addWidget(lableHistory);
    historyLayout->addWidget(tableHistory);
    historyLayout->addWidget(hLine());
    historyLayout->addWidget(histograph);

    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(historyLayout);

    setLayout(mainLayout);

    setWindowTitle(STR_DIALOG_TITLE_CARD_INFO);
}

void CardInfoDialog::closeEvent(QCloseEvent *event)
{
    setSetting(SETTING_HISTORY_COLUMN_TIME, tableHistory->columnWidth(0));
    setSetting(SETTING_HISTORY_COLUMN_LEVEL, tableHistory->columnWidth(1));

    QxDialog::closeEvent(event);
}

void CardInfoDialog::setCard(Card *card)
{
    QList<Point*> points = card->getHistory()->getPoints();

    QStandardItemModel *model = new QStandardItemModel(points.size(), 2, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(STR_CARD_HISTORY_TIME));
    model->setHorizontalHeaderItem(1, new QStandardItem(STR_CARD_HISTORY_LEVEL));

    for (int index = 0; index < points.size(); ++index)
    {
        model->setItem(index, 0, new QStandardItem(points[index]->time.toString()));
        model->setItem(index, 1, new QStandardItem(LevelsName[points[index]->level]));
    }

    tableHistory->setModel(model);
    tableHistory->setColumnWidth(0, getSetting(SETTING_HISTORY_COLUMN_TIME, 100).toInt());
    tableHistory->setColumnWidth(1, getSetting(SETTING_HISTORY_COLUMN_LEVEL, 20).toInt());

    histograph->setHistory(card->getHistory());
}
