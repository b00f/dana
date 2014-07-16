/* * Dana - Dana, Symbol of Wisdom
 * Copyright (C) 2014 Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
 *
 * This file is part of Dana.
 *
 * Dana is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dana is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dana.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DECKLISTDATAMODEL_H
#define __DECKLISTDATAMODEL_H

#include <QAbstractItemModel>


class DeckList;
class DeckListDataModel 
    : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Roles {
     TypeRole   = Qt::UserRole,
     NameRole                 ,
     DescRole                 ,
     PixmapRole               ,
     CardNumberRole           ,
     DownloadsRole            ,
     RatingRole               ,
     RatingStateRole          ,
     CreatedTimeRole          ,
     UpdatedTimeRole          ,
     InternalPointerRole
    };

    explicit DeckListDataModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    void setDeckList(DeckList *deckList);

private:
    DeckList *deckList;
};

#endif // __DECKLISTDATAMODEL_H