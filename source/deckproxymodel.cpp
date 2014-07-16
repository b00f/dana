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

#include "deckproxymodel.h"
#include "deckdatamodel.h"
#include "constants.h"
#include "card.h"

DeckProxyModel::DeckProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    filterLevel = Level_ALL;
}

bool DeckProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int column = sortColumn();

    const QString l_front = left.data(DeckDataModel::FrontRole).toString();
    const QString r_front = right.data(DeckDataModel::FrontRole).toString();
    
    bool lessThan = (QString::compare(l_front, r_front, Qt::CaseInsensitive) < 0);

    switch(column)
    {
    case DeckDataModel::ColumnFront:
        break;

    case DeckDataModel::ColumnStarred:
    {
        bool leftStared = left.data(DeckDataModel::StarredRole).toBool();
        bool rightStared = right.data(DeckDataModel::StarredRole).toBool();

        if(leftStared && rightStared)
            return lessThan;

        if(leftStared)
            return true;

        if(rightStared)
            return false;
    }
        break;

    case DeckDataModel::ColumnDifficulty:
    {
        int leftDifficulty = left.data(DeckDataModel::DifficultyRole).toInt();
        int rightDifficulty = right.data(DeckDataModel::DifficultyRole).toInt();

        if(leftDifficulty < rightDifficulty)
            return true;

        if(leftDifficulty > rightDifficulty)
            return false;
    }
        break;

    case DeckDataModel::ColumnProgress:
    {
        int leftProgress = left.data(DeckDataModel::LevelRole).toInt();
        int rightProgress = right.data(DeckDataModel::LevelRole).toInt();

        if(leftProgress < rightProgress)
            return true;

        if(leftProgress > rightProgress)
            return false;
    }
        break;
    }


    return lessThan;
}

bool DeckProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    if (!index.isValid())
		return false;

    if(filterLevel != Level_ALL)
    {
        int cardLevel = index.data(DeckDataModel::LevelRole).toInt();

        if(filterLevel != cardLevel)
            return false;
    }

    QRegExp filterFront = filterRegExp();

    if(filterFront.isValid())
    {
        QString front = index.data(DeckDataModel::FrontRole).toString();
        return (filterFront.indexIn(front) != -1);
    }

    return true;
}

void DeckProxyModel::refresh()
{
    ///blockSignals(true);
    invalidate();
    ///blockSignals(false);

    ////emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void DeckProxyModel::setFilterLevel(int level)
{
    filterLevel = level;
}