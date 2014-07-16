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

#include "decklistproxymodel.h"
#include "decklistdatamodel.h"
#include "constants.h"
#include "decklist.h"
#include "ideck.h"
#include "deck.h"

DeckListProxyModel::DeckListProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool DeckListProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{

    QVariant leftData = left.data( sortRole() );
    QVariant rightData = right.data( sortRole() );

    if ( rightData.isNull() )
        return false;
    
    if ( leftData.isNull() )
        return true;
    
    switch ( leftData.type() )
    {
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        {
            return leftData.toLongLong() > rightData.toLongLong();
        }
        
    case QVariant::Double:
        return leftData.toDouble() > rightData.toDouble();

    case QVariant::Date:
        return leftData.toDate() > rightData.toDate();

    case QVariant::DateTime:
        return leftData.toDateTime() > rightData.toDateTime();

    default:
        return (QString::compare(leftData.toString(), rightData.toString(), Qt::CaseInsensitive) < 0);
    }
    
    return false;
}

bool DeckListProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    if (!index.isValid())
		return false;

    QString name = index.data(DeckListDataModel::NameRole).toString();

    QRegExp filterFront = filterRegExp();

    if(filterFront.isValid())
    {
        return (filterFront.indexIn(name) != -1);
    }

    return true;
}


void DeckListProxyModel::refresh()
{
    ///blockSignals(true);
    invalidate();
    ///blockSignals(false);

    ////emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}