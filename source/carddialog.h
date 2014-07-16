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

#ifndef __CARDDIALOG_H
#define __CARDDIALOG_H

#include "qxdialog.h"
#include "cardquery.h"
#include "combolabel.h"
#include "danaeditor.h"
#include "clicktoshowbutton.h"

class Deck;
class Card;
class DeckFormat;
class CardDialog 
    : public QxDialog
{
    Q_OBJECT
public:
    enum Mode{Add=0,Edit,Query,Study,Format};

    explicit CardDialog(Mode mode, QWidget *parent = 0);

    void setCard(Card *card);
    void initializeForQuery(Deck *deck);
    void setDeckPath(QString path);

    void setFormat(DeckFormat deckFormat);
    void getFormat(DeckFormat &deckFormat);

signals:
    void addCard(Card *card);
    void newCard();

private slots:
    void onShowQuerySide();
    void onChangeQuerySide(int);
    void onChangeFilterLevel(int);
    void onSave();
    void onExit();
    void onQueryPass();
    void onQueryFail();
    void onNextCard();
    void onPrevCard();
    void onFinish(int result);
    void onTextChange();

private:
    void setupView();

    void hideQuerySide();
    void showQuerySide();
    void setModified(bool modified = true);

    bool eventFilter(QObject *watched, QEvent *event);
    void showEvent(QShowEvent *event);

    void showNextCard();

private:
    DanaEditor	*editFront;
    DanaEditor	*editBack;
    QCheckBox   *chkKeepOpen;
    ComboLabel  *comboFilterLevel;
    ComboLabel  *comboQuerySide;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnNext;
    QPushButton *btnPrev;
    QPushButton *btnExit;
    QPushButton *btnSave;
    QPushButton *btnNew;
    QSplitter   *splitter;

    ClickToShowButton *btnHideBack;
    ClickToShowButton *btnHideFront;
    
    bool hideBack;
    bool hasModified;
    Mode mode;

    Card *card;
    CardQuery *cardQuery;
};

#endif // __CARDDIALOG_H
