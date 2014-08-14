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

#include "decklist.h"
#include "decklistwidget.h"
#include "deckitemdelegate.h"
#include "decklistdatamodelsingle.h"
#include "deck.h"


DeckListWidget::DeckListWidget(QWidget *parent)
    : QListView(parent)
{
    contextMenu = 0;
    proxyModel = 0;
    dataModel = 0;
    searchBox = new SearchEdit(this);
    itemDelegate = new DeckItemDelegate(this);

    setItemDelegate(itemDelegate);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(itemDelegate, SIGNAL(voted(const QModelIndex ,int)),
        this, SLOT(onVote(const QModelIndex ,int)));

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));

    connect(this, SIGNAL(activated(QModelIndex)),
            this, SIGNAL(activated()));
    
    setMinimumWidth(500);

    ///searchBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    ///setStyleSheet(QString("QListView{margin-top:%1;background-color:white;border-bottom:1px solid black;}").arg(searchBox->height()+2));
}

void DeckListWidget::hideSearchBox(bool hide)
{
    if(hide) {
        searchBox->hide();
        setStyleSheet("QListView{margin-top:0;}");
    } else {
        searchBox->show();
        setStyleSheet(QString("QListView{margin-top:%1;}").arg(searchBox->height()+2));
    }
}

void DeckListWidget::addDeck(Deck *deck)
{
    dataModel = new DeckListDataModelSingle(this);
    
    ((DeckListDataModelSingle *)dataModel)->setDeck(deck);
    
    setModel(dataModel);

    hideSearchBox();
}

void DeckListWidget::setDeckList(DeckList *deckList)
{
    dataModel = new DeckListDataModel(this);
    proxyModel = new DeckListProxyModel(this);

    dataModel->setDeckList(deckList);

    proxyModel->setSourceModel(dataModel);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->sort(0);

    setModel(proxyModel);
        
    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SIGNAL(selectionChanged()));

    connect(searchBox, SIGNAL(textChanged(QString)), 
        proxyModel, SLOT(setFilterWildcard(QString)));
}

Deck *DeckListWidget::getSelectedDeck(int* row)
{
    QModelIndex index = currentIndex();

    if(index.isValid()) {
        if(row)
            *row = index.row();

        return index.data(DeckListDataModel::InternalPointerRole).value<Deck*>();
    }

    return 0;
}

void DeckListWidget::selectRow(int row)
{
    QModelIndex index = model()->index(row, 0);

    if(!index.isValid()) {
        index = model()->index(0, 0);
    }

    setCurrentIndex(index);

    emit selectionChanged();
}

void DeckListWidget::setContextMenu(QMenu *menu)
{
    contextMenu = menu;
}

void DeckListWidget::ShowContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    if(!index.isValid())
        return;

    if(contextMenu) {
        QPoint globalPos = mapToGlobal(pos);

        contextMenu->exec(globalPos);
    }
}

int DeckListWidget::getRowHeight()
{
    return sizeHintForRow(0);
}

void DeckListWidget::onVote(const QModelIndex &index, int rating)
{
    if(index.isValid()) {

        Deck* deck = index.data(DeckListDataModel::InternalPointerRole).value<Deck*>();

        emit voted(deck, rating);
    }
}

void DeckListWidget::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    QScrollBar *scrollBarr = horizontalScrollBar();

    if(scrollBarr)
        width += scrollBarr->sizeHint().width();

    searchBox->resize(width, 0);

    QListView::resizeEvent(event);
}

void DeckListWidget::setSortRole(int role)
{
    if(proxyModel)
        proxyModel->setSortRole(role);
}

void DeckListWidget::setViewOption(int option)
{
    itemDelegate->setViewOption(option);

    if(proxyModel)
        proxyModel->refresh();
}
