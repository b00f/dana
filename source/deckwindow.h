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

#ifndef __DECKWINDOW_H
#define __DECKWINDOW_H

#include "carddialog.h"
#include "deckwidget.h"
#include "childwindow.h"
#include "querydialog.h"
#include "reviewdialog.h"
#include "cardinfodialog.h"

class MyDeck;
class DeckWindow 
    : public ChildWindow
{
    Q_OBJECT

public:
    explicit DeckWindow(QMainWindow *parent = 0);

    void setDeck(MyDeck *deck);

    bool isRunningQuickQuery();
    void showQuickQuery();

signals:
    void openDesk();
    void quickQuery(bool);

private slots:
    void onEditCard();
    void onRemoveCard();
    void onAddCard(Card *card);
    void onOpenCard(Card *card);
    void onSave();
    void onQuery();
    void onStudy();
    void onReport();
    void onReview();
    void onNewCard();
    void onSetLevel(QAction *action);
    void onSelectionChang();
    void onTurnStar();
    void onOpenDesk();
    void onStopQuickQuery();
    void onQuickQuery();
    void updateView();
    void onCardInfo();

private:
    void setupToolbar();
    void setupActions();
    void setupView();
    void setupMenu();
    void setupContextMenu();
    Card *getSelectedCard(int *rowNo = 0);

    void setupCardDialogSignals(CardDialog *dlg);

private:
    DeckWidget *deckWidget;

    QAction *actDesk,
            *actAdd,
            *actEdit,
            *actStar,
            *actRemove,
            *actSave,
            *actQuery,
            *actStudy,
            *actReport,
            *actReview,
            *actCardInfo,
            *actQuickQuery;

    MyDeck *deck;

	QueryDialog *qqDlg;
    ReviewDialog *reviewDlg;
    CardInfoDialog *infoDlg;
    
    QMenu *contextMent;
    QMenu *levelMenu;

    int newCardCounter;
};

#endif // __DECKWINDOW_H
