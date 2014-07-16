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

#ifndef __DECKLISTWIDGET_H
#define __DECKLISTWIDGET_H

#include "decklistproxymodel.h"
#include "decklistdatamodel.h"
#include "deckitemdelegate.h"
#include "searchedit.h"
#include "decklist.h"

#include <QtGui>
#include <QtDebug>
#include <QtWidgets>

class Deck;
class DeckListWidget 
    : public QListView
{
    Q_OBJECT

public:
    explicit DeckListWidget(QWidget *parent = 0);

    void setDeckList(DeckList *deckList);
    void addDeck(Deck *deck);
    void setContextMenu(QMenu *menu);
    int getRowHeight();

    Deck *getSelectedDeck(int* row = 0);
    void selectRow(int row);

    void setSortRole(int role);
    void setViewOption(int option);

    void hideSearchBox(bool hide = true);

signals:
    void selectionChanged();
    void activated();
    void voted(Deck* deck, int rating);

private slots:
    void ShowContextMenu(const QPoint &pos);
    void onVote(const QModelIndex &index, int rating);
    
private:
    void resizeEvent(QResizeEvent *event);

private:
    SearchEdit *searchBox;
    QMenu *contextMenu;

    DeckListDataModel *dataModel;
    DeckListProxyModel *proxyModel;

    DeckItemDelegate *itemDelegate;
};

#endif // __DECKLISTWIDGET_H