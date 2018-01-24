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

#include "deckdatamodel.h"
#include "deck.h"
#include "card.h"

#include <QRegExp>

DeckDataModel::DeckDataModel(QObject *parent)
	: QAbstractItemModel(parent)
    , deck(0)
{
}


int DeckDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if(!deck)
        return 0;

    return deck->getTotalCardsNo();
}

int DeckDataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent); 

    return ColumnCount;
}

QVariant DeckDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    Card *card = static_cast<Card*>(index.internalPointer());

    if(!card)
        return QVariant();

    switch(role) {
    case Qt::DisplayRole:
        switch(index.column())  {
        case ColumnFront:      return card->getFrontPlain();
        case ColumnProgress:   return Card::getLevelPercentage( card->getLevel() );
        case ColumnStarred:    return QVariant();
        case ColumnDifficulty: return card->getDifficulty();
        case ColumnCreation:   return card->getCreationTime().toString("dd.MM.yyyy hh:mm");
        } break;

    case Qt::ForegroundRole:
        if(index.column()==ColumnProgress) {
            return Card::getLevelColor( card->getLevel() );
        } break;

    case Qt::TextAlignmentRole: 
        if(index.column() == ColumnFront)
            return QVariant(Qt::AlignLeft|Qt::AlignVCenter);
        else
            return QVariant(Qt::AlignCenter|Qt::AlignVCenter);

        /// user roles
    case FrontRole:
        return card->getFrontPlain();

    case LevelRole:
        return card->getLevel();

    case StarredRole:
        return card->isStarred();

    case DifficultyRole:
        return card->getDifficulty();

    case CreationRole:
        return card->getCreationTime();

    case InternalPointerRole:
        return QVariant::fromValue(card);
    }

    return QVariant();
}

QVariant DeckDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case ColumnFront:
            return tr("Front");

        case ColumnProgress:
            return tr("Progress");

        case ColumnStarred:
            return tr("");

        case ColumnDifficulty:
            return tr("Difficulty");

        case ColumnCreation:
            return tr("Creation");

		default:
            return QVariant();
        }
    }
    return QVariant();
}

bool DeckDataModel::insertRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row+1);


    endInsertRows();
    return true;
}

bool DeckDataModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), row, row+1);

    endRemoveRows();
    return true;
}

Qt::ItemFlags DeckDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index);
}

QModelIndex DeckDataModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    Card *card = deck->getCardAt(row);

    if(card)
        return createIndex(row, column, card);

    return QModelIndex();
}

bool DeckDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == StarredRole) {
        Card *card = static_cast<Card*>(index.internalPointer());

        card->turnStarFlag();
    }

    return QAbstractItemModel::setData(index, value, role);
}

QModelIndex DeckDataModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

void DeckDataModel::setDeck(Deck *_deck)
{
    deck = _deck;
}
