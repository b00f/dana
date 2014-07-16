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

#ifndef __DECKTABLE_H
#define __DECKTABLE_H

#include "searchedit.h"

#include <QTableView>
#include <QSortFilterProxyModel>

class Card;
class DeckTable 
    : public QTableView
{
    Q_OBJECT

public:
    explicit DeckTable(QWidget *parent = 0);

    void setModel(QSortFilterProxyModel *model);

    void showHorizontalHeader(bool show = false);
    void setContextMenu(QMenu *menu);

    Card *getSelectedCard(int *row = 0);
    void selectRow(int row);

signals:
    void activated();
    void selectionChanged();

private slots:
    void ShowContextMenu(const QPoint &pos);

private:
    void resizeEvent(QResizeEvent *event);

public:
    QPen *gridPen;

private:
    SearchEdit *searchBox;
    QMenu *contextMenu;
};

#endif // __DECKTABLE_H