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

#include "carddialog.h"
#include "verticallabel.h"
#include "qxmessagebox.h"
#include "preferences.h"
#include "constants.h"
#include "deckformat.h"
#include "deck.h"
#include "card.h"


#define SETTING_QUERY_SIDE_INDEX          "query_side_index"
#define SETTING_FILTER_LEVEL_INDEX_STUDY  "filter_level_index_study"
#define SETTING_FILTER_LEVEL_INDEX_QUERY  "filter_level_index_query"
#define SETTING_SPLITTER_STATE            "splitter_state"

CardDialog::CardDialog(Mode mode, QWidget *parent)
    : QxDialog("card_dialog", parent)
    , mode(mode)
    , card(0)
    , cardQuery(0)
{
    setupView();

    setModified(false);
    ///installEventFilter(this);
}

void CardDialog::setupView()
{
    editFront = new DanaEditor;
    editBack = new DanaEditor;
    splitter = new QSplitter(Qt::Vertical);
    comboFilterLevel = 0;
    comboQuerySide = 0;
    chkKeepOpen = 0;
    btnHideBack = 0;
    btnHideFront = 0;
	btnUp = 0;
	btnDown = 0;
	btnNext = 0;
	btnPrev = 0;

    splitter->setStyleSheet("QSplitter::handle:pressed { background-color: gray }");

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish(int)));
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *headerLayout = new QHBoxLayout;
    QVBoxLayout *editLayout   = new QVBoxLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;

    QWidget *frontSide;
    {
        frontSide = new QWidget;
        QGridLayout *frontLayout = new QGridLayout;
        VerticalLabel *lblFront = new VerticalLabel(STR_CARD_FRONT_SIDE);

        //lblFront->setStyleSheet("QLabel{font-weight:bold; letter-spacing:1px}");

        frontLayout->addWidget(vLine2() ,0,0,1,1);
        frontLayout->addWidget(lblFront ,1,0,1,1);
        frontLayout->addWidget(vLine2() ,2,0,1,1);
        frontLayout->addWidget(editFront,0,1,3,1);

        editFront->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        connect(editFront, SIGNAL(textChanged()), this, SLOT(onTextChange()));

        /// click to show button
        btnHideFront = new ClickToShowButton;
        btnHideFront->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(btnHideFront, SIGNAL(clicked()), this, SLOT(onShowQuerySide()));
        frontLayout->addWidget(btnHideFront,0,1,3,1);
        btnHideFront->hide();

        frontLayout->setMargin(0);

        frontSide->setLayout(frontLayout);
    }

    QWidget *backSide;
    {
        backSide = new QWidget;
        QGridLayout *backLayout= new QGridLayout;
        VerticalLabel *lblBack = new VerticalLabel(STR_CARD_BACK_SIDE);

        //lblBack->setStyleSheet("QLabel{font-weight:bold; letter-spacing:1px}");

        backLayout->addWidget(vLine2(),0,0,1,1);
        backLayout->addWidget(lblBack ,1,0,1,1);
        backLayout->addWidget(vLine2(),2,0,1,1);
        backLayout->addWidget(editBack,0,1,3,1);

        editFront->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        connect(editBack, SIGNAL(textChanged()), this, SLOT(onTextChange()));

        /// click to show button
        btnHideBack = new ClickToShowButton;
        btnHideBack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(btnHideBack, SIGNAL(clicked()), this, SLOT(onShowQuerySide()));
        backLayout->addWidget(btnHideBack,0,1,3,1);
        btnHideBack->hide();

        backLayout->setMargin(0);

        backSide->setLayout(backLayout);
    }

    //footerLayout
    {
        btnExit = new QPushButton(ICON_EXIT, STR_NOPE);
        btnSave = new QPushButton(ICON_SAVE, STR_CARD_SAVE);
        btnNew  = new QPushButton (ICON_CARD_NEW, STR_NOPE);

        btnExit->setToolTip(STR_EXIT_DIALOG_TIP);
        btnSave->setToolTip(STR_CARD_SAVE_TIP);
        btnNew->setToolTip(STR_CARD_NEW_TIP);

        btnSave->setShortcut(QKeySequence("Ctrl+S"));

        connect(btnExit, SIGNAL(clicked()), this, SLOT(onExit()));
        connect(btnSave, SIGNAL(clicked()), this, SLOT(onSave()));
        connect(btnNew, SIGNAL(clicked()), this, SIGNAL(newCard()));

        btnSave->setDefault(true);
    }

    switch (mode) {
    case Add:{
        chkKeepOpen = new QCheckBox(STR_CARD_DIALOG_KEEP_OPEN);

        chkKeepOpen->setChecked(false);
        editFront->showToolbar();
        editBack->showToolbar();

        footerLayout->addWidget(chkKeepOpen);

        setWindowTitle(STR_DIALOG_TITLE_ADD_CARD);
             } break;

    case Edit: {
        editFront->showToolbar();
        editBack->showToolbar();

        setWindowTitle(STR_DIALOG_TITLE_EDIT_CARD);        
               } break;

    case Query: {
        QGridLayout *gridQuery = new QGridLayout;

        btnUp   = new QPushButton(ICON_THUMB_UP  , STR_CARD_EASY);
        btnDown = new QPushButton(ICON_THUMB_DOWN, STR_CARD_HARD);
        btnNext = new QPushButton(ICON_NEXT      , STR_NOPE);
        btnPrev = new QPushButton(ICON_PREV      , STR_NOPE);

        QLabel *label = new QLabel(STR_QUERY_QUESTION);

        btnUp  ->setToolTip(STR_CARD_EASY_TIP);
        btnDown->setToolTip(STR_CARD_HARD_TIP);
        btnNext->setToolTip(STR_CARD_NEXT_TIP);
        btnPrev->setToolTip(STR_CARD_PREV_TIP);

        btnNext->setShortcut(QKeySequence("Right"));
        btnPrev->setShortcut(QKeySequence("Left"));
        btnUp->setShortcut(QKeySequence("Up"));
        btnDown->setShortcut(QKeySequence("Down"));
        
        /// ---- level filter combo
        comboFilterLevel = new ComboLabel(ICON_FILTER);
        comboFilterLevel->addItem(STR_ALL_LEVELS, Level_ALL);
        for(int index=0;index<LevelCount; index++) {
            comboFilterLevel->addItem(LevelsName[index], index);
        }

        int filterLevelIndex = getSetting(SETTING_FILTER_LEVEL_INDEX_QUERY).toInt();
        comboFilterLevel->setCurrentIndex(filterLevelIndex);

        connect(comboFilterLevel, SIGNAL(comboIndexChanged(int)), this, SLOT(onChangeFilterLevel(int)));
        /// ---- 

        /// ---- query side combo
        comboQuerySide = new ComboLabel(ICON_FLIP);
        comboQuerySide->addItem(STR_QUERY_FRONT_2_BACK);
        comboQuerySide->addItem(STR_QUERY_BACK_2_FRONT);

        int querySideIndex = getSetting(SETTING_QUERY_SIDE_INDEX).toInt();

        comboQuerySide->setCurrentIndex(querySideIndex);
        connect(comboQuerySide, SIGNAL(comboIndexChanged(int)), this, SLOT(onChangeQuerySide(int)));
        /// ---- 

        connect(btnNext, SIGNAL(clicked()), this, SLOT(onNextCard()));
        connect(btnPrev, SIGNAL(clicked()), this, SLOT(onPrevCard()));
        connect(btnUp,   SIGNAL(clicked()), this, SLOT(onQueryPass()));
        connect(btnDown, SIGNAL(clicked()), this, SLOT(onQueryFail()));
        
        gridQuery->setSpacing(0);
        gridQuery->addWidget(label    , 0, 0, 1, 5, Qt::AlignCenter);
        gridQuery->addWidget(btnPrev  , 1, 0, 1, 1);
        gridQuery->addWidget(btnDown  , 1, 1, 1, 1);
        gridQuery->addItem  (hSpacer(), 1, 2, 1, 1);
        gridQuery->addWidget(btnUp    , 1, 3, 1, 1);
        gridQuery->addWidget(btnNext  , 1, 4, 1, 1);

        headerLayout->addLayout(gridQuery);

        footerLayout->addWidget(comboFilterLevel);
        //footerLayout->addWidget(vLine());
        footerLayout->addWidget(comboQuerySide);

        cardQuery = new CardQuery();

        onChangeQuerySide(querySideIndex);
        onChangeFilterLevel(filterLevelIndex);
        setWindowTitle(STR_DIALOG_TITLE_QUERY);
                } break;

    case Study: {
        btnNext = new QPushButton(ICON_NEXT, STR_CARD_NEXT);
        btnPrev = new QPushButton(ICON_PREV, STR_CARD_PREV);

        btnNext->setToolTip(STR_CARD_NEXT_TIP);
        btnPrev->setToolTip(STR_CARD_PREV_TIP);

        btnNext->setShortcut(QKeySequence("Right"));
        btnPrev->setShortcut(QKeySequence("Left"));

        connect(btnNext, SIGNAL(clicked()), this, SLOT(onNextCard()));
        connect(btnPrev, SIGNAL(clicked()), this, SLOT(onPrevCard()));

        /// ---- level filter combo
        comboFilterLevel = new ComboLabel(ICON_FILTER);
        comboFilterLevel->addItem(STR_ALL_LEVELS, Level_ALL);
        for(int index=0;index<LevelCount; index++) {
            comboFilterLevel->addItem(LevelsName[index], index);
        }

        int filterLevelIndex = getSetting(SETTING_FILTER_LEVEL_INDEX_STUDY).toInt();
        comboFilterLevel->setCurrentIndex(filterLevelIndex);

        connect(comboFilterLevel, SIGNAL(comboIndexChanged(int)), this, SLOT(onChangeFilterLevel(int)));
        /// ---- 
        
        headerLayout->setSpacing(0);
        headerLayout->addWidget(btnPrev);
        headerLayout->addItem(hSpacer());
        headerLayout->addWidget(btnNext);

        footerLayout->addWidget(comboFilterLevel);

        cardQuery = new CardQuery();

        onChangeFilterLevel(filterLevelIndex);

        setWindowTitle(STR_DIALOG_TITLE_STUDY);
                } break;

    case Format: {
        editFront->setText(STR_CARD_FORMAT_SAMPLE_TEXT);
        editBack ->setText(STR_CARD_FORMAT_SAMPLE_TEXT);

        editFront->setReadOnly(true);
        editBack ->setReadOnly(true);

        editFront->showToolbar();
        editBack ->showToolbar();

        setWindowTitle(STR_DIALOG_TITLE_FORMAT);
                 } break;
    }

    footerLayout->addItem(hSpacer());

    if(mode!=Format) {
        footerLayout->addWidget(btnNew);
        footerLayout->addWidget(vLine());
    }
    footerLayout->addWidget(btnSave);
    footerLayout->addWidget(btnExit);

    splitter->addWidget(frontSide);
    splitter->addWidget(backSide);

    editLayout->addWidget(splitter);

    /// mainLayout->setSpacing(4);
    /// mainLayout->setMargin(4);

    mainLayout->addLayout(headerLayout);
    mainLayout->addItem(hSpacer());
    mainLayout->addLayout(editLayout);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);

    setLayout(mainLayout);    

    splitter->restoreState(getSetting(SETTING_SPLITTER_STATE).toByteArray());


    if(btnNext)
        btnNext->setFocus();

    if(btnUp)
        btnUp->setFocus();
}

void CardDialog::initializeForQuery(Deck *deck)
{
    cardQuery->setDeck(deck);
    cardQuery->shuffle();
    showNextCard();
}

void CardDialog::setDeckPath(QString path)
{
    editFront->setDeckPath(path);
    editBack ->setDeckPath(path);
}

void CardDialog::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
}

void CardDialog::onFinish(int result)
{
    Q_UNUSED(result)

    setSetting(SETTING_SPLITTER_STATE, splitter->saveState());

    switch(mode) {
    case Add: 
    case Edit: 
    case Format:
        break;

    case Query:
        setSetting(SETTING_FILTER_LEVEL_INDEX_QUERY, comboFilterLevel->currentIndex());
        setSetting(SETTING_QUERY_SIDE_INDEX, comboQuerySide->currentIndex());
        break;

    case Study:
        setSetting(SETTING_FILTER_LEVEL_INDEX_STUDY, comboFilterLevel->currentIndex());
        break;
    }
}

void CardDialog::onShowQuerySide()
{
    showQuerySide();
}

void CardDialog::hideQuerySide()
{
    if(hideBack){
        btnHideBack->show();
        btnHideFront->hide();

        editBack->hide();
        editFront->show();
    } else {
        btnHideBack->hide();
        btnHideFront->show();

        editBack->show();
        editFront->hide();
    }
}

void CardDialog::showQuerySide()
{
    QWidget *w = this->focusWidget();

    if(hideBack){
        btnHideBack->hide();
        editBack->show();
    } else {
        btnHideFront->hide();
        editFront->show();
    }

    w->setFocus();
}

void CardDialog::onChangeQuerySide(int index)
{
    hideBack = (index==0);

    hideQuerySide();
}

void CardDialog::onChangeFilterLevel(int index)
{
    int filterLevel = comboFilterLevel->itemData(index).toInt();

    cardQuery->setFilterLevel(filterLevel);
    /*
    /// don't change current card, if level matches.
    if(card) {
        if(filterLevel==Level_ALL)
            return;

        if(filterLevel==card->getLevel())
            return;
    }

    showNextCard();
    */
}

void CardDialog::onSave()
{
    setModified(false);

    /// format mode has no card
    if(card) {
        card->updateFront(editFront->getText());
        card->updateBack(editBack->getText());
    }

    switch(mode) {
    case Add: {
        emit addCard(card);

        if(chkKeepOpen->isChecked()) {
            setCard(new Card);
        } else {
            accept();
        }
              } break;

    case Edit: {
        accept();
               } break;

    case Query:
    case Study: {
                } break;

    case Format: {

        accept();
                 } break;
    }
}

void CardDialog::onExit()
{
    switch(mode) {
    case Add: {
            delete card;
        } break;

    case Edit:
    case Query:
    case Study:
    case Format: {
        } break;
    }

    reject();
}

void CardDialog::onQueryPass()
{
    card->increaseLevel();

    onNextCard();
}

void CardDialog::onQueryFail()
{
    card->decreaseLevel();

    onNextCard();
}

void CardDialog::onNextCard()
{
    setCard(cardQuery->gotoNextCard());
}

void CardDialog::onPrevCard()
{
    setCard(cardQuery->gotoPrevCard());
}

void CardDialog::showNextCard()
{
    Card *card = cardQuery->gotoNextCard();

    setCard(card);    
}

void CardDialog::setCard(Card *_card)
{
    /// check if the card has changed
    if(hasModified) {
        if( QxMessageBox::question(this, WNG_CARD_CHANGED, WNG_CARD_CHANGED_TITLE) ==
            QxMessageBox::Yes) {
                onSave();
        }
    }

    editFront->clear();
    editBack->clear();

    card=_card;

    if(card) {
        btnSave->setEnabled(true);
        editFront->setEnabled(true);
        editBack->setEnabled(true);
        
        editFront->setText(card->getFront());
        editBack->setText(card->getBack());

        switch (mode) {
        case Add:
        case Edit:
            {
                editFront->setFocus();
            } break;

        case Query:
            {
                btnUp->setEnabled(true);
                btnDown->setEnabled(true);
                btnPrev->setEnabled(cardQuery->hasPrevCard());
                btnNext->setEnabled(cardQuery->hasNextCard());

                btnUp->setFocus();

                hideQuerySide();
            } break;

        case Study:
            {
                btnPrev->setEnabled(cardQuery->hasPrevCard());
                btnNext->setEnabled(cardQuery->hasNextCard());

                btnNext->setFocus();
            } break;

        case Format: {
                     } break;
        }
    } else {
        btnSave->setDisabled(true);
        editFront->setDisabled(true);
        editBack->setDisabled(true);

        switch (mode) {
        case Add:
        case Edit:
            break;

        case Query: {
            btnUp->setDisabled(true);
            btnDown->setDisabled(true);
            btnNext->setDisabled(true);
            btnPrev->setDisabled(true);
                    }
                    break;

        case Study: {
            btnNext->setDisabled(true);
            btnPrev->setDisabled(true);
                    } break;

        case Format: {
                     } break;
        }
    }

    setModified(false);
}

void CardDialog::onTextChange()
{
    setModified(true);
}

void CardDialog::setModified(bool modified)
{
    hasModified = modified;
    btnSave->setEnabled(modified);
}

bool CardDialog::eventFilter(QObject *watched, QEvent *event)
{
    return QxDialog::eventFilter(watched, event);
}

void CardDialog::getFormat(DeckFormat &deckFormat)
{
    editFront->getTextFormat(deckFormat.frontCharFormat, deckFormat.frontBlockFormat);
    editBack->getTextFormat(deckFormat.backCharFormat, deckFormat.backBlockFormat);
}

void CardDialog::setFormat(DeckFormat deckFormat)
{
    if(mode!=Format) {
        editFront->setAcceptRichText(deckFormat.frontEditorPolicy == DeckFormat::AcceptRich);
        editBack->setAcceptRichText (deckFormat.backEditorPolicy  == DeckFormat::AcceptRich);
    }

    editFront->setTextFormat(deckFormat.frontCharFormat, deckFormat.frontBlockFormat);
    editBack->setTextFormat(deckFormat.backCharFormat, deckFormat.backBlockFormat);
}
