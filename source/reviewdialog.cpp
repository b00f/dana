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

#include "reviewdialog.h"
#include "constants.h"
#include "deck.h"

ReviewDialog::ReviewDialog(QWidget *parent)
    : QxDialog("review_dialog", parent)
{
    dataModel = new DeckDataModel(this);
    proxyModel = new DeckProxyModel(this);

    setupView();
}

void ReviewDialog::setupView()
{
    deckTable = new DeckTable;

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *headerLayout = new QHBoxLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;

    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(deckTable);
    mainLayout->addLayout(footerLayout);

    connect(deckTable, SIGNAL(activated()), this, SIGNAL(activated()));
    connect(deckTable, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));

    setLayout(mainLayout);

    setWindowTitle(STR_DIALOG_TITLE_REVIEW);
}

void ReviewDialog::setDeck(Deck *deck)
{
    dataModel->setDeck(deck);

    proxyModel->setSourceModel(dataModel);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->sort(DeckDataModel::ColumnFront);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    deckTable->showHorizontalHeader(true);
    deckTable->setModel(proxyModel);    
}

void ReviewDialog::setContextMenu(QMenu *menu)
{
    deckTable->setContextMenu(menu);
}

Card *ReviewDialog::getSelectedCard(int *row)
{
    return deckTable->getSelectedCard(row);
}

void ReviewDialog::selectRow(int row)
{
    deckTable->selectRow(row);
}