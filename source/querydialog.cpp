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

#include <QLocale>

QueryDialog::QueryDialog(QWidget *parent)
    : QxDialog("query_dialog", parent)
{
    speech = new QTextToSpeech(this);
    speech->setLocale(QLocale("en_US"));
    card = 0;
    running = false;

    setupView();
}

void QueryDialog::setupView()
{
    iconStar.addPixmap(PIXMAP_STARRED,   QIcon::Normal, QIcon::On);
    iconStar.addPixmap(PIXMAP_UNSTARRED, QIcon::Normal, QIcon::Off);

    btnUp          = new QPushButton(ICON_THUMB_UP  , STR_NOPE, this);
    btnDown        = new QPushButton(ICON_THUMB_DOWN, STR_NOPE, this);
    btnNext        = new QPushButton(ICON_NEXT      , STR_NOPE, this);
    btnPrev        = new QPushButton(ICON_PREV      , STR_NOPE, this);
    btnReview      = new QPushButton(ICON_CARD_OPEN , STR_NOPE, this);
    btnPause       = new QPushButton(ICON_STOP      , STR_NOPE, this);
    btnListen      = new QPushButton(ICON_LISTEN    , STR_NOPE, this);
    btnStar        = new QPushButton(iconStar       , STR_NOPE, this);
    lblFront       = new QLabel(this);
    lblLevel       = new QLabel(this);
    lblDifficaulty = new QLabel(this);
    histograph     = new Histograph(this);
    mainTimer      = new QTimer(this);

    connect(btnUp,     SIGNAL(clicked()), this, SLOT(onQueryPass()));
    connect(btnDown,   SIGNAL(clicked()), this, SLOT(onQueryFail()));
    connect(btnNext,   SIGNAL(clicked()), this, SLOT(onNextCard()));
    connect(btnPrev,   SIGNAL(clicked()), this, SLOT(onPrevCard()));
    connect(btnReview, SIGNAL(clicked()), this, SLOT(onOpenCard()));
    connect(btnListen, SIGNAL(clicked()), this, SLOT(onListen()));
    connect(btnStar,   SIGNAL(clicked()), this, SLOT(onTurnStar()));
    connect(btnPause,  SIGNAL(clicked()), this, SLOT(stop()));

    btnUp     ->setToolTip(STR_CARD_EASY_TIP        );
    btnDown   ->setToolTip(STR_CARD_HARD_TIP        );
    btnNext   ->setToolTip(STR_CARD_NEXT_TIP        );
    btnPrev   ->setToolTip(STR_CARD_PREV_TIP        );
    btnReview ->setToolTip(STR_CARD_REVIEW_TIP      );
    btnPause  ->setToolTip(STR_QUERY_STOP_QUERY_TIP );
    btnStar   ->setToolTip(STR_CARD_PREV_TIP        );
    btnListen ->setToolTip(STR_CARD_LISTEN          );
    histograph->setToolTip(STR_QUERY_HISTOGRAPH_TIP );

    lblFront->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lblFront->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    lblFront->setWordWrap(true);

    btnStar->setCheckable(true);

    QVBoxLayout *mainLayout =  new QVBoxLayout(this);
    QVBoxLayout *queryLayout = new QVBoxLayout;
    QHBoxLayout *statusLayout = new QHBoxLayout;
    QHBoxLayout *toolsLayout = new QHBoxLayout;

    statusLayout->addWidget(histograph);
    statusLayout->addStretch();
    statusLayout->addWidget(lblDifficaulty);
    statusLayout->addWidget(lblLevel);

    queryLayout->addWidget(lblFront);
    queryLayout->addLayout(statusLayout);

    toolsLayout->addWidget(btnPause);
    toolsLayout->addStretch();
    toolsLayout->addWidget(btnReview);
    toolsLayout->addWidget(btnListen);
    toolsLayout->addWidget(btnStar);
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
    btnListen->setShortcut(Qt::CTRL + Qt::Key_D);

    btnReview->setFocusPolicy(Qt::NoFocus);

    mainLayout->addLayout(queryLayout);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(toolsLayout);

    connect(mainTimer, SIGNAL(timeout()), this, SLOT(show()));

    int mainTimerInterval = Preferences::GetInstance()->getQueryInterval();

    mainTimer->setInterval(MIN_2_MSEC(mainTimerInterval));

    /*if(getSetting("geometry").isNull())*/{
        QScreen *screen = QGuiApplication::screens()[0];
        QRect r = screen->availableGeometry();

        int x = r.right()-500;
        int y = r.bottom()-200;

        setGeometry(x-5,y-5,500,200);
    }

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

    cardQuery.shuffle();

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
    cardQuery.setDeck(deck);

    deckFormat = deck->getFormat();
}

void QueryDialog::onPrevCard()
{
    setCard(cardQuery.gotoPrevCard());
}

void QueryDialog::onNextCard()
{
    setCard(cardQuery.gotoNextCard());
}

void QueryDialog::onQueryPass()
{
    card->increaseLevel();

    setCard(cardQuery.gotoNextCard());
}

void QueryDialog::onQueryFail()
{
    card->decreaseLevel();

    setCard(cardQuery.gotoNextCard());
}

void QueryDialog::setCard(Card *_card)
{
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
        btnPrev->setEnabled(cardQuery.hasPrevCard());
        btnNext->setEnabled(cardQuery.hasNextCard());
        btnStar->setChecked(card->isStarred());

        histograph->setHistory(card->getHistory(), true);

    } else {
        btnReview->setEnabled(false);
        btnPrev->setEnabled(false);
        btnNext->setEnabled(false);
        btnUp->setEnabled(false);
        btnDown->setEnabled(false);
        btnStar->setEnabled(false);

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

        hide();

        event->ignore();
    }
    else {
        mainTimer->stop();
        mainTimer->disconnect();

        event->accept();

        stop();
    }

    QxDialog::closeEvent(event);
}

void QueryDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    mainTimer->stop();
}

void QueryDialog::onListen()
{
    if(card) {
        speech->say(card->getFrontPlain());
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

void QueryDialog::onTurnStar()
{
    card->turnStarFlag();

    if(btnStar->isChecked()) {
        btnStar->setChecked(true);
    } else {
        btnStar->setChecked(false);
    }

}
