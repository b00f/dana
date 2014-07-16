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

#include "decklistdatamodel.h"
#include "decklist.h"
#include "ideck.h"
#include "deck.h"

#include <QRegExp>

DeckListDataModel::DeckListDataModel(QObject *parent)
	: QAbstractItemModel(parent)
    , deckList(0)
{
}

int DeckListDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(!deckList)
        return 0;

    return deckList->getCount();
}

int DeckListDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent); 

    return 1;
}

QVariant DeckListDataModel::data(const QModelIndex &index, int role) const
{
    Deck* deck = (Deck *)index.internalPointer();

    if(!deck)
        return QVariant();

    switch(role) {
    case TypeRole:            return deck->getType();
    case NameRole:            return deck->getName();
    case DescRole:            return deck->getDesc();
    case PixmapRole:          return deck->getPixmap();
    case CardNumberRole:      return deck->getInHandCardsNo();
    case DownloadsRole:       return ((iDeck *)deck)->getDownloads();
    case RatingRole:          return ((iDeck *)deck)->getRating();
    case CreatedTimeRole:     return deck->getCreatedTime();
    case UpdatedTimeRole:     return deck->getUpdatedTime();
    case InternalPointerRole: return QVariant::fromValue(deck);
    }

    return QVariant();
}

QVariant DeckListDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    Q_UNUSED(orientation);
    Q_UNUSED(role);

    return QVariant();
}

bool DeckListDataModel::insertRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row+1);

    endInsertRows();
    return true;
}

bool DeckListDataModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row+1);

    endRemoveRows();
    return true;
}

Qt::ItemFlags DeckListDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index);
}

QModelIndex DeckListDataModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    Deck *deck = deckList->getDeckAt(row);

    if(deck)
        return createIndex(row, column, deck);

    return QModelIndex();
}

QModelIndex DeckListDataModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

void DeckListDataModel::setDeckList(DeckList *_deckList)
{
    deckList = _deckList;
}
