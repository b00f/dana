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

#ifndef __REVIEWDIALOG_H
#define __REVIEWDIALOG_H

#include "qxdialog.h"
#include "decktable.h"
#include "deckdatamodel.h"
#include "deckproxymodel.h"

class Deck;
class ReviewDialog 
    : public QxDialog
{
    Q_OBJECT

public:
    explicit ReviewDialog(QWidget *parent = 0);

    void  setDeck(Deck *deck);
    void  setContextMenu(QMenu *menu);
    Card *getSelectedCard(int *row = 0);
    void selectRow(int row);

signals:
    void activated();
    void selectionChanged();

private:
    void setupView();

private:
    DeckTable *deckTable;

    DeckDataModel *dataModel;
    DeckProxyModel *proxyModel;
};

#endif // __REVIEWDIALOG_H