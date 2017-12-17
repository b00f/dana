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

#ifndef __QUERYDIALOG_H
#define __QUERYDIALOG_H


#include "qxdialog.h"
#include "deckformat.h"
#include "histograph.h"
#include "cardquery.h"

#include <QTimer>
#include <QTextToSpeech>

class Deck;
class Card;
class QueryDialog 
    : public QxDialog
{
    Q_OBJECT

public:
    explicit QueryDialog(QWidget *parent = 0);

    void setDeck(Deck *deck);
    bool isRunning();

signals:
    Card *getNextCard(int filterLevel, Card *prevCard);
    void openCard(Card *card);

public slots:
    void stop();
    void start();
    
private slots:
    void onOpenCard();
    void onQueryPass();
    void onQueryFail();
    void onPrevCard();
    void onNextCard();
    void onTurnStar();
    void onListen();

private:
    void setupView();
    void setCard(Card *card);
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void reject();

    QString formatHtml(const QString &text);

private:
    QLabel *lblFront;
    QPushButton *btnUp;
    QPushButton *btnDown;
    QPushButton *btnNext;
    QPushButton *btnPrev;
    QPushButton *btnReview;
    QPushButton *btnListen;
    QPushButton *btnStar;
    QPushButton *btnPause;
    QLabel *lblLevel;
    QLabel *lblDifficaulty;
    Histograph *histograph;
    
    Card *card;

    QTimer *mainTimer;

    bool running;

    QTextToSpeech *speech;
    QAction *actListen;

    CardQuery cardQuery;
    DeckFormat deckFormat;
    QIcon iconStar;
};

#endif // __QUERYDIALOG_H
