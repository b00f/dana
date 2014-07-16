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

#ifndef __DECKWIDGET_H
#define __DECKWIDGET_H

#include "constants.h"
#include "decktable.h"
#include "deckdatamodel.h"
#include "deckproxymodel.h"
#include "qxpushbutton.h"

#include <QtGui>
#include <QSortFilterProxyModel>

class Deck;
class DeckWidget 
    : public QWidget
{
    Q_OBJECT

public:
    explicit DeckWidget(QWidget *parent = 0);

    void setDeck(Deck *deck);
    void setContextMenu(QMenu *menu);

    Card *getSelectedCard(int *row = 0);
    void selectRow(int row);

    void updateView();

signals:
    void selectionChanged();
    void activated();

private slots:
    
private slots:
    void filter(int level);

private:
    void setupToolbar();
    void setupView();
    void setupActions();
    void setupContextMenu();

protected:

private:
    QxPushButton *deckLevels[LevelCount];
    DeckTable *deckTable;

    DeckDataModel *dataModel;
    DeckProxyModel *proxyModel;

    Deck *deck;
};

#endif // __DECKWIDGET_H