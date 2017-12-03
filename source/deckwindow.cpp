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

#include "deckwindow.h"
#include "reviewdialog.h"
#include "reportdialog.h"
#include "qxmessagebox.h"
#include "constants.h"
#include "mydeck.h"
#include "card.h"


DeckWindow::DeckWindow(QMainWindow *parent)
    : ChildWindow(parent)
{
    setupView();
    setupActions();
    setupToolbar();
    setupMenu();
    setupContextMenu();

    deck = 0;
	newCardCounter = 0;

    qqDlg = new QueryDialog(this);
    reviewDlg = new ReviewDialog(this);

    qqDlg->hide();
    reviewDlg->hide();

    reviewDlg->setContextMenu(contextMent);

    connect(qqDlg, SIGNAL(finished(int)), this, SLOT(onStopQuickQuery()));
    connect(qqDlg, SIGNAL(openCard(Card*)), this, SLOT(onOpenCard(Card*)));
    connect(reviewDlg, SIGNAL(selectionChanged()), this, SLOT(onSelectionChang()));
    connect(reviewDlg, SIGNAL(activated()), this, SLOT(onEditCard()));
}

void DeckWindow::setupView()
{
    deckWidget = new DeckWidget(this);

    mainLayout->addWidget(deckWidget);

    connect(deckWidget, SIGNAL(selectionChanged()), this, SLOT(onSelectionChang()));
    connect(deckWidget, SIGNAL(activated()), this, SLOT(onEditCard()));
}

void DeckWindow::setupToolbar()
{
    toolbar->addAction(actDesk);
    toolbar->addAction(actStudy);
    /// toolbar->addAction(actQuery);
    toolbar->addAction(actQuickQuery);
    toolbar->addAction(actReview);
    /// toolbar->addAction(actReport);
    toolbar->addSeparator();
    toolbar->addAction(actAdd);
    toolbar->addAction(actRemove);
    toolbar->addSeparator();
    toolbar->addAction(actAbout);
}

void DeckWindow::setupMenu()
{
    mainMenu->clear();

    /// Card Menu
    QMenu *cardMenu = mainMenu->addMenu(STR_MENU_CARD);
    cardMenu->addAction(actAdd);
    cardMenu->addAction(actEdit);
    cardMenu->addAction(actRemove);
    cardMenu->addSeparator();
    cardMenu->addAction(actQuit);

    /// Action Menu
    QMenu *actionMenu = mainMenu->addMenu(STR_MENU_ACTION);
    actionMenu->addAction(actDesk);
    actionMenu->addSeparator();
    actionMenu->addAction(actSave);
    actionMenu->addAction(actQuery);
    actionMenu->addAction(actQuickQuery);
    actionMenu->addAction(actStudy);
    actionMenu->addAction(actReview);
    actionMenu->addAction(actReport);
    actionMenu->addSeparator();
    actionMenu->addAction(actConfig);

    ChildWindow::setupMenu();
}

void DeckWindow::setupActions()
{
    actDesk = new QAction(ICON_DESK, STR_ACTION_BACK_TO_DESK, this);
    actDesk->setShortcut(QKeySequence("BackSpace"));
    actDesk->setStatusTip(STR_ACTION_BACK_TO_DESK_TIP);
    connect(actDesk, SIGNAL(triggered()), this, SLOT(onOpenDesk()));

    actAdd = new QAction(ICON_CARD_NEW, STR_ACTION_CARD_NEW, this);
    actAdd->setShortcut(QKeySequence("Insert"));
    actAdd->setStatusTip(STR_ACTION_CARD_NEW_TIP);
    connect(actAdd, SIGNAL(triggered()), this, SLOT(onNewCard()));
    
    actEdit = new QAction(ICON_CARD_OPEN, STR_ACTION_CARD_OPEN, this);
    actEdit->setEnabled(false);
    actEdit->setStatusTip(STR_ACTION_CARD_OPEN_TIP);
    connect(actEdit, SIGNAL(triggered()), this, SLOT(onEditCard()));

	actRemove = new QAction(ICON_CARD_REMOVE, STR_ACTION_CARD_REMOVE, this);
    actRemove->setEnabled(false);
    actRemove->setShortcut(QKeySequence("Delete"));
    actRemove->setStatusTip(STR_ACTION_CARD_REMOVE);
    connect(actRemove, SIGNAL(triggered()), this, SLOT(onRemoveCard()));

    actStar = new QAction(ICON_STARRED, STR_ACTION_CARD_STAR, this);
    actStar->setEnabled(false);
    actStar->setStatusTip(STR_ACTION_CARD_STAR_TIP);
    connect(actStar, SIGNAL(triggered()), this, SLOT(onTurnStar()));

    actSave = new QAction(ICON_DECK_SAVE, STR_ACTION_DECK_SAVE, this);
    actSave->setShortcut(QKeySequence("Ctrl+s"));
    actSave->setStatusTip(STR_ACTION_DECK_SAVE_TIP);
    connect(actSave, SIGNAL(triggered()), this, SLOT(onSave()));

    actQuery = new QAction(ICON_DECK_QUERY, STR_ACTION_DECK_QUERY, this);
    actQuery->setShortcut(QKeySequence("F5"));
    actQuery->setStatusTip(STR_ACTION_DECK_QUERY_TIP);
    connect(actQuery, SIGNAL(triggered()), this, SLOT(onQuery()));

    actQuickQuery = new QAction(ICON_DECK_QUICK_QUERY, STR_ACTION_DECK_QUICK_QUERY, this);
    actQuickQuery->setShortcut(QKeySequence("F6"));
    actQuickQuery->setStatusTip(STR_ACTION_DECK_QUICK_QUERY_TIP);
    actQuickQuery->setCheckable(true);
    connect(actQuickQuery, SIGNAL(triggered()), this, SLOT(onQuickQuery()));

    actStudy = new QAction(ICON_DECK_STUDY, STR_ACTION_DECK_STUDY, this);
    actStudy->setShortcut(QKeySequence("F7"));
    actStudy->setStatusTip(STR_ACTION_DECK_STUDY_TIP);
    connect(actStudy, SIGNAL(triggered()), this, SLOT(onStudy()));

    actReview = new QAction(ICON_DECK_REVIEW, STR_ACTION_DECK_REVIEW, this);
    actReview->setShortcut(QKeySequence("F8"));
    actReview->setStatusTip(STR_ACTION_DECK_REVIEW_TIP);
    connect(actReview, SIGNAL(triggered()), this, SLOT(onReview()));

    actReport= new QAction(ICON_DECK_REPORT, STR_ACTION_DECK_REPORT, this);
    actReport->setStatusTip(STR_ACTION_DECK_REPORT_TIP);
    connect(actReport, SIGNAL(triggered()), this, SLOT(onReport()));

    ChildWindow::setupActions();
}

void DeckWindow::setupContextMenu()
{
    levelMenu = new QMenu(STR_MENU_CARD_SET_LEVEL, this);
    for(int index=0; index<LevelCount; index++) {
        QAction *action = new QAction(LevelsName[index], this);
        action->setData(index);
        levelMenu->addAction(action);
    }

    levelMenu->setEnabled(false);

    connect(levelMenu, SIGNAL(triggered(QAction*)), this, SLOT(onSetLevel(QAction*)));

    contextMent = new QMenu(this);

    contextMent->addAction(actEdit);
    contextMent->addAction(actRemove);
    contextMent->addAction(actStar);
    contextMent->addSeparator();
    contextMent->addMenu(levelMenu);

    deckWidget->setContextMenu(contextMent);
}

void DeckWindow::updateView()
{
    deckWidget->updateView();
}

void DeckWindow::setDeck(MyDeck *_deck)
{
    deck = _deck;

    /// update title
    title->setText(deck->getName());

    /// setup models
    deckWidget->setDeck(deck);
    
    updateView();
}

void DeckWindow::onNewCard()
{
    CardDialog *dlg= new CardDialog(CardDialog::Add, this);

	if(qobject_cast<CardDialog *>(sender())) {
		QString title = dlg->windowTitle();
		dlg->setWindowTitle(QString("%1 #%2").arg(title).arg(++newCardCounter));
        QRect g = dlg->geometry();
        g.translate(20*newCardCounter,20*newCardCounter);
        dlg->setGeometry(g);
	} else {
		newCardCounter = 0;
	}

    setupCardDialogSignals(dlg);

    dlg->setCard(new Card);
	dlg->show();
}

void DeckWindow::onAddCard(Card *card)
{
    deck->addCard(card);

    updateView();
}

void DeckWindow::setupCardDialogSignals(CardDialog *dlg)
{
    connect(dlg, SIGNAL(addCard(Card*)), this, SLOT(onAddCard(Card*)));
    connect(dlg, SIGNAL(finished(int)), this, SLOT(updateView()));
    connect(dlg, SIGNAL(newCard()), this, SLOT(onNewCard()));

    dlg->setDeckPath(deck->getDeckPath());
    dlg->setFormat(deck->getFormat());
}

void DeckWindow::onEditCard()
{
    Card *card = getSelectedCard();

    if(card)
        onOpenCard(card);
}

void DeckWindow::onOpenCard(Card *card)
{
    QWidget *parent = this;
    if(sender()->isWidgetType())
        parent = (QWidget*)sender(); /// might it is review dialog

    CardDialog *dlg = new CardDialog(CardDialog::Edit, parent);

    setupCardDialogSignals(dlg);

    dlg->setCard(card);
    dlg->show();
}

void DeckWindow::onRemoveCard()
{
    int index;
    Card *card = getSelectedCard(&index);

    if(!card)
        return;

    if( QxMessageBox::question(this, WNG_REMOVE_CARD.arg(card->getFrontPlain()) , WNG_REMOVE_CARD_TITLE) == 
        QxMessageBox::Yes) {
        deck->removeOneCard(card);
        updateView();

        deckWidget->selectRow(index);
    }
}

void DeckWindow::onSave()
{
    deck->saveDeck();
}

void DeckWindow::onQuery()
{
    CardDialog *dlg = new CardDialog(CardDialog::Query, this) ;

    setupCardDialogSignals(dlg);

    dlg->initializeForQuery(deck);
    dlg->show();
}

void DeckWindow::onStudy()
{
    CardDialog *dlg = new CardDialog(CardDialog::Study, this) ;

    setupCardDialogSignals(dlg);

    dlg->initializeForQuery(deck);
    dlg->show();
}

Card *DeckWindow::getSelectedCard(int *rowNo)
{
    if(reviewDlg->isVisible())
        return reviewDlg->getSelectedCard(rowNo);

    return deckWidget->getSelectedCard(rowNo);
}

void DeckWindow::onReport()
{
    ReportDialog dlg(this);

    dlg.setupModel(deck);

    dlg.exec();
}

void DeckWindow::onReview()
{
    reviewDlg->setDeck(deck);
    reviewDlg->exec();
}

void DeckWindow::onSetLevel(QAction *action)
{
    Card *card = getSelectedCard();

    if(!card)
        return;

    card->updateLevel(action->data().toInt());

    updateView();
}

void DeckWindow::onSelectionChang()
{
    Card *card = getSelectedCard();

    if(card) {
        actEdit->setEnabled(true);
        actRemove->setEnabled(true);
        actStar->setEnabled(true);
        levelMenu->setEnabled(true);
    } else {
        actEdit->setEnabled(false);
        actRemove->setEnabled(false);
        actStar->setEnabled(false);
        levelMenu->setEnabled(false);
    }
}

void DeckWindow::onTurnStar()
{
    Card *card = getSelectedCard();

    if(!card)
        return;

    card->turnStarFlag();

    repaint();
}

void DeckWindow::onOpenDesk()
{
    if(qqDlg->isRunning())
        qqDlg->stop();

    deck->closeDeck();

    emit openDesk();
}

void DeckWindow::onStopQuickQuery()
{
    bool running = isRunningQuickQuery();
    if(running) {
        ///_ASSERT(0);
    }

    emit quickQuery(false);
    actQuickQuery->setChecked(false);
}

void DeckWindow::onQuickQuery()
{
    bool running = isRunningQuickQuery();
    if(running) {
        qqDlg->stop();
    } else {
        qqDlg->setDeck(deck);
        qqDlg->start();
    }

    emit quickQuery(!running);
    actQuickQuery->setChecked(!running);
}

void DeckWindow::showQuickQuery()
{
    qqDlg->show();
}

bool DeckWindow::isRunningQuickQuery()
{
    return qqDlg->isRunning();
}
