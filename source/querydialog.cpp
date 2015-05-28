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

#include "querydialog.h"
#include "preferences.h"
#include "qxmessagebox.h"
#include "constants.h"
#include "deck.h"
#include "card.h"


QueryDialog::QueryDialog(QWidget *parent)
    : QxDialog("query_dialog", parent)
{
    speech = new QtSpeech;
    card = 0;
    cardQuery = 0;
    running = false;

    setupView();
}

QueryDialog::~QueryDialog()
{
    delete speech;
}

void QueryDialog::setupView()
{
    cardQuery = new CardQuery;

    QVBoxLayout *mainLayout =  new QVBoxLayout(this);
    QVBoxLayout *queryLayout = new QVBoxLayout;
    QHBoxLayout *statusLayout = new QHBoxLayout;
    QHBoxLayout *toolsLayout = new QHBoxLayout;

    lblFront       = new QLabel;
    btnUp          = new QPushButton(ICON_THUMB_UP  , STR_NOPE);
    btnDown        = new QPushButton(ICON_THUMB_DOWN, STR_NOPE);
    btnNext        = new QPushButton(ICON_NEXT      , STR_NOPE);
    btnPrev        = new QPushButton(ICON_PREV      , STR_NOPE);
    btnReview      = new QPushButton(ICON_CARD_OPEN , STR_NOPE);
    btnPause       = new QPushButton(ICON_STOP      , STR_NOPE);
    lblLevel       = new QLabel;
    lblDifficaulty = new QLabel;
    histograph     = new Histograph;
    mainTimer      = new QTimer(this);
    closeTimer     = new QTimer(this);

    connect(btnUp,     SIGNAL(clicked()), this, SLOT(onQueryPass()));
    connect(btnDown,   SIGNAL(clicked()), this, SLOT(onQueryFail()));
    connect(btnNext,   SIGNAL(clicked()), this, SLOT(onNextCard()));
    connect(btnPrev,   SIGNAL(clicked()), this, SLOT(onPrevCard()));
    connect(btnReview, SIGNAL(clicked()), this, SLOT(onOpenCard()));
    connect(btnPause,  SIGNAL(clicked()), this, SLOT(stop()));

    btnUp     ->setToolTip(STR_CARD_EASY_TIP        );
    btnDown   ->setToolTip(STR_CARD_HARD_TIP        );
    btnNext   ->setToolTip(STR_CARD_NEXT_TIP        ); 
    btnPrev   ->setToolTip(STR_CARD_PREV_TIP        );
    btnReview ->setToolTip(STR_CARD_REVIEW_TIP      );
    btnPause  ->setToolTip(STR_QUERY_STOP_QUERY_TIP );
    histograph->setToolTip(STR_QUERY_HISTOGRAPH_TIP );

    lblFront->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lblFront->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    lblFront->setWordWrap(true);

    statusLayout->addWidget(histograph);
    statusLayout->addStretch();
    statusLayout->addWidget(lblDifficaulty);
    statusLayout->addWidget(lblLevel);

    queryLayout->addWidget(lblFront);
    queryLayout->addLayout(statusLayout);

    toolsLayout->addWidget(btnPause);
    toolsLayout->addStretch();
    toolsLayout->addWidget(btnReview);
    toolsLayout->addWidget(vLine());
    toolsLayout->addWidget(btnDown);
    toolsLayout->addWidget(btnUp);
    toolsLayout->addWidget(vLine());
    toolsLayout->addWidget(btnPrev);
    toolsLayout->addWidget(btnNext);

    btnUp    ->setShortcut(QKeySequence("Up"  ));
    btnDown  ->setShortcut(QKeySequence("Down"));
    btnPrev  ->setShortcut(QKeySequence("Left"));
    btnNext  ->setShortcut(QKeySequence("Right"));
    btnReview->setShortcut(QKeySequence("Space"));

    btnReview->setFocusPolicy(Qt::NoFocus);

    mainLayout->addLayout(queryLayout);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(toolsLayout);

    connect(mainTimer, SIGNAL(timeout()), this, SLOT(show()));
    connect(closeTimer, SIGNAL(timeout()), this, SLOT(close()));

    int closeTimerInterval = 2; /// close this dialog if user doesn't reaction for two minutes.
    int mainTimerInterval = Preferences::GetInstance()->getQueryInterval();
    
    /// close this dialog if user doesn't reaction for two minutes.
    closeTimer->setInterval(MIN_2_MSEC(closeTimerInterval));
    mainTimer->setInterval(MIN_2_MSEC(mainTimerInterval));
    
    /*if(getSetting("geometry").isNull())*/{
        QDesktopWidget desktop;
        QRect r = desktop.availableGeometry();

        int x = r.right()-500;
        int y = r.bottom()-200;

        setGeometry(x-5,y-5,500,200);
    }

    actListen = new QAction(STR_ACTION_LISTEN_IT, this);
    actListen->setShortcut(Qt::CTRL + Qt::Key_D);
    addAction(actListen);
    connect(actListen, SIGNAL(triggered(bool)), this, SLOT(listen()));

    btnUp->setFocus();

    histograph->setFixedWidth(120);
    histograph->setFixedHeight(40);

    setWindowTitle(STR_DIALOG_TITLE_QUERY);
}

bool QueryDialog::isRunning()
{
    return running;
}

void QueryDialog::start()
{
    running = true;
    
    cardQuery->shuffle();

    onNextCard();
    show();
}

void QueryDialog::stop()
{
    running = false;
    
    QTimer::singleShot(0, this, SLOT(accept()));
}

void QueryDialog::onOpenCard()
{
    emit openCard(card);
}

void QueryDialog::setDeck(Deck *deck)
{
    cardQuery->setDeck(deck);

    deckFormat = deck->getFormat();
}

void QueryDialog::onPrevCard()
{
    setCard(cardQuery->gotoPrevCard());
}

void QueryDialog::onNextCard()
{
    setCard(cardQuery->gotoNextCard());
}

void QueryDialog::onQueryPass()
{
    card->increaseLevel();

    setCard(cardQuery->gotoNextCard());

    listen();
}

void QueryDialog::onQueryFail()
{
    card->decreaseLevel();

    setCard(cardQuery->gotoNextCard());

    listen();
}

void QueryDialog::setCard(Card *_card)
{
    closeTimer->start();
    lblFront->clear();

    card=_card;

    if(card) {
        lblFront->setText(formatHtml(card->getFront()));
        lblLevel->setText(Card::getLevelString( card->getLevel() ));
        lblDifficaulty->setPixmap(Card::getDifficultyPixmap( card->getDifficulty() ));
        lblDifficaulty->setToolTip(Card::getDifficultyString( card->getDifficulty() ));

        btnReview->setEnabled(true);
        btnUp->setEnabled(true);
        btnDown->setEnabled(true);
        btnPrev->setEnabled(cardQuery->hasPrevCard());
        btnNext->setEnabled(cardQuery->hasNextCard());

        QMap<time_t, int> history;
        card->getHistory().getMap(history);
        histograph->setData(history);        

    } else {
        btnReview->setEnabled(false);
        btnPrev->setEnabled(false);
        btnNext->setEnabled(false);
        btnUp->setEnabled(false);
        btnDown->setEnabled(false);
        
        stop();
    }
}

void QueryDialog::reject()
{
    QxDialog::close();
}

void QueryDialog::closeEvent(QCloseEvent *event)
{
    if(running) {
        mainTimer->start();
        closeTimer->stop();

        hide();

        event->ignore();        
    }
    else {
        mainTimer->stop();
        closeTimer->stop();

        mainTimer->disconnect();
        closeTimer->disconnect();

        event->accept();

        stop();
    }
}

void QueryDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    closeTimer->start();
    mainTimer->stop();
}

void QueryDialog::listen()
{
    try {
        speech->stop();
        speech->tell(card->getFrontPlain());
    }catch(...) {
        QxMessageBox::critical(this, ERR_QT_SPEECH_FAILED);
    }
}

QString QueryDialog::formatHtml(const QString &text)
{
    QString align;
    Qt::Alignment a = deckFormat.frontBlockFormat.alignment();

    if (a & Qt::AlignLeft) {
        align="left";
    } else if (a & Qt::AlignHCenter) {
        align="center";
    } else if (a & Qt::AlignRight) {
        align="right";
    } else if (a & Qt::AlignJustify) {
        align="justify";
    }

    QString fontFamily = deckFormat.frontCharFormat.font().family();
    QString fontSize = QString::number(deckFormat.frontCharFormat.font().pointSize());
    QString fontWeight = deckFormat.frontCharFormat.font().bold()?"bold":"normal";
    QString fontStyle = deckFormat.frontCharFormat.font().italic()?"italic":"normal";
    QString textColor = deckFormat.frontCharFormat.foreground().color().name();
    QString textDecoration = deckFormat.frontCharFormat.font().underline()?"underline":"none";

    QString html = QString("<html><body align='%1'><p style='font-family:%2; font-weight:%3; font-style:%4; font-size:%5pt; color:%6; text-decoration:%7; margin:0px; padding:0px'>%8</p></body></html>")
        .arg(align)
        .arg(fontFamily)
        .arg(fontWeight)
        .arg(fontStyle)
        .arg(fontSize)
        .arg(textColor)
        .arg(textDecoration)
        .arg(text);

    return html;
}
