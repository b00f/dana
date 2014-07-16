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

#include "decktable.h"
#include "deckdatamodel.h"
#include "carditemdelegate.h"
#include "card.h"

#include <QMenu>
#include <QLayout>
#include <QScrollBar>
#include <QTableView>
#include <QResizeEvent>
#include <QHeaderView>


DeckTable::DeckTable(QWidget *parent)
    : QTableView(parent)
{
    searchBox = new SearchEdit(this);

    verticalHeader()->hide();
    horizontalHeader()->hide();

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setItemDelegate(new CardItemDelegate(this));
    setSortingEnabled(true);
    setShowGrid(false);
    //setMouseTracking(true);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));

    connect(this, SIGNAL(activated(const QModelIndex &)),
            this, SIGNAL(activated()));

    searchBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setStyleSheet(QString("QTableView{margin-top:%1;background-color:white;border-bottom:1px solid black;}").arg(searchBox->height()+2));
}

void DeckTable::setModel(QSortFilterProxyModel *model)
{
    QTableView::setModel(model);

    connect(searchBox, SIGNAL(textChanged(QString)), model, SLOT(setFilterWildcard(QString)));

    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SIGNAL(selectionChanged()));

    horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnFront, QHeaderView::Stretch);

    if(horizontalHeader()->isHidden()) {
        horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnProgress, QHeaderView::Fixed);
        horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnDifficulty, QHeaderView::Fixed);
        horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnStarred, QHeaderView::Fixed);

        horizontalHeader()->resizeSection (DeckDataModel::ColumnProgress, 60);
        horizontalHeader()->resizeSection (DeckDataModel::ColumnDifficulty, 40);
        horizontalHeader()->resizeSection (DeckDataModel::ColumnStarred, 30);
    } else {
        horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnProgress, QHeaderView::ResizeToContents);
        horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnDifficulty, QHeaderView::ResizeToContents);
        horizontalHeader()->setSectionResizeMode(DeckDataModel::ColumnStarred, QHeaderView::ResizeToContents);
    }

    searchBox->clear();
}

void DeckTable::setContextMenu(QMenu *menu)
{
    contextMenu = menu;
}

void DeckTable::ShowContextMenu(const QPoint &pos)
{
    QModelIndex index = indexAt(pos);

    if(!index.isValid())
        return;

    if(contextMenu) {
        QPoint globalPos = mapToGlobal(pos);

        contextMenu->exec(globalPos);
    }
}

Card *DeckTable::getSelectedCard(int *row)
{
    QModelIndex index = currentIndex();

    if(index.isValid()) {
        if(row)
            *row = index.row();

        return index.data(DeckDataModel::InternalPointerRole).value<Card*>();
    }

    return 0;
}

void DeckTable::selectRow(int row)
{
    QModelIndex index = model()->index(row, 0);

    if(!index.isValid()) {
        index = model()->index(0, 0);
    }

    setCurrentIndex(index);

    emit selectionChanged();
}

void DeckTable::showHorizontalHeader(bool show)
{
    horizontalHeader()->setVisible(show);
}

void DeckTable::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    QScrollBar *scrollBarr = verticalScrollBar();

    if(scrollBarr->isVisible())
        width += scrollBarr->sizeHint().width();

    searchBox->resize(width, 0);

    QTableView::resizeEvent(event);
}
