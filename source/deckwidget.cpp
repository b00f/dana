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

#include "deckwidget.h"
#include "carddialog.h"
#include "qxpushbutton.h"
#include "deck.h"

#include <QtGui>
#include <QDebug>
#include <QDomElement>
#include <QSignalMapper>


DeckWidget::DeckWidget(QWidget *parent)
    : QWidget(parent)
{
    dataModel = new DeckDataModel(this);
    proxyModel = new DeckProxyModel(this);

    setupView();
}

void DeckWidget::setupView()
{
    deckTable = new DeckTable(this);

    QGridLayout *mainLayout = new QGridLayout(this);
    QVBoxLayout *leftLayout = new QVBoxLayout;

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    leftLayout->setSpacing(4);
    leftLayout->setContentsMargins(0,0,6,0);

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSignalMapper *signalMapper = new QSignalMapper(this);

    for(int i=0;i<LevelCount;i++) {
        deckLevels[i] = new QxPushButton(this);
        deckLevels[i]->setMinimumSize(QSize(150, 0));
        deckLevels[i]->setCheckable(true);
        deckLevels[i]->setSizePolicy(sizePolicy);

        leftLayout->addWidget(deckLevels[i], LevelCount-i);
        signalMapper->setMapping(deckLevels[i], i);

        connect(deckLevels[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(filter(int)));

    deckLevels[0]->setChecked(true);

    hLine = new QFrame(this);

    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);
    hLine->setMinimumSize(QSize(150, 0));
    hLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    deckStars = new QxPushButton(this);
    deckStars->setCheckable(true);
    deckStars->setMinimumSize(QSize(150, 0));
    deckStars->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    signalMapper->setMapping(deckStars, Level_Starred);
    connect(deckStars, SIGNAL(clicked()), signalMapper, SLOT(map()));

    leftLayout->addWidget(hLine);
    leftLayout->addWidget(deckStars, Level_Starred);

    mainLayout->addLayout(leftLayout,0,0,2,1);
    mainLayout->addWidget(deckTable,1,1,1,1);

    connect(deckTable, SIGNAL(activated()), this, SIGNAL(activated()));
    connect(deckTable, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));
}

void DeckWidget::filter(int level)
{
    QString lable;
    for(int l = 0; l < LevelCount; l++) {

        QString count = deck->getCardsNo_str(l);

        if(l==level) {
            lable = QString("<b>%1</b><br/><small>%2</small>")
                .arg(LevelsName[l])
                .arg(count);

            deckLevels[l]->setChecked(true);
        } else {
            lable = QString("%1<br/><small>%2</small>")
                .arg(LevelsName[l])
                .arg(count);

            deckLevels[l]->setChecked(false);
        }

        deckLevels[l]->setHtml(lable);
    }

    QPixmap pixmap(PIXMAP_STARRED);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    pixmap.save(&buffer, "PNG");
    lable = QString("<div style=\"vertical-align: middle\"><img src=\"data:image/png;base64,") + byteArray.toBase64() + "\"/> " +
            QString("<small>(%1)</small></div>").arg(deck->getCardsNo_str(Level_Starred));
    
    deckStars->setHtml(lable);
    deckStars->setChecked(level==Level_Starred);

    proxyModel->setFilterLevel(level);
    
    updateView();
}

void DeckWidget::setDeck(Deck *_deck)
{
    deck = _deck;

    dataModel->setDeck(deck);

    proxyModel->setSourceModel(dataModel);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->sort(DeckDataModel::ColumnStarred);

    deckTable->setModel(proxyModel);
    deckTable->hideColumn(DeckDataModel::ColumnProgress);

    filter(0);
}

void DeckWidget::updateView()
{
    proxyModel->refresh();
    deckTable->hideColumn(DeckDataModel::ColumnProgress);
}

void DeckWidget::setContextMenu(QMenu *menu)
{
    deckTable->setContextMenu(menu);
}

Card *DeckWidget::getSelectedCard(int *row)
{
    return deckTable->getSelectedCard(row);
}

void DeckWidget::selectRow(int row)
{
   deckTable->selectRow(row);
}
