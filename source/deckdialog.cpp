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

#include "deckdialog.h"
#include "clickablelabel.h"
#include "carddialog.h"
#include "constants.h"
#include "deck.h"

#include <math.h>

DeckDialog::DeckDialog(Mode mode, QWidget *parent)
    : QxDialog("deck_dialog", parent)
    , deck(0)
    , mode(mode)
{
	setupView();

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void DeckDialog::setupView()
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	QGridLayout *editLayout = new QGridLayout;
	QHBoxLayout *footerLayout = new QHBoxLayout;

	//editLayout
	{
        iconBtn = new IconButton;
        nameEdit = new QLineEdit;
        descEdit = new QPlainTextEdit;
        authorEdit = new QLineEdit;
        tagsEdit = new QLineEdit;
        createdEdit = new QLineEdit;
        updatedEdit = new QLineEdit;
        guidEdit = new QLineEdit;
        frontPolicyCombo = new ComboLabel(QIcon());
        backPolicyCombo = new ComboLabel(QIcon());

        QLabel *authorLabel  = new QLabel(STR_DECK_AUTHOR);
        QLabel *guidLabel    = new QLabel(STR_DECK_GUID);
        QLabel *tagsLabel    = new QLabel(STR_DECK_TAGS);
        QLabel *createdLabel = new QLabel(STR_DECK_CREATED_TIME);
        QLabel *updatedLabel = new QLabel(STR_DECK_UPDATED_TIME);
        QLabel *formatLabel  = new QLabel(STR_DECK_CARD_FORMAT);
        QLabel *tagTipLabel  = new QLabel(STR_DECK_TAGS_HELP);
        QLabel *frontPolicyLabel = new QLabel(STR_DECK_FRONT_POLICY_LABEL);
        QLabel *backPolicyLabel  = new QLabel(STR_DECK_BACK_POLICY_LABEL);

        ClickableLabel *formatLink = new ClickableLabel(STR_DECK_CHANGE_FORMAT_LINK, this);

        connect(formatLink, SIGNAL(clicked()), this, SLOT(onChangeFormat()));

        iconBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        nameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        descEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		editLayout->setSpacing(2);
        editLayout->setMargin(2);

        nameEdit->setFixedHeight(22);
        ///descEdit->setFixedHeight(40);

        nameEdit->setStyleSheet("font-weight:bold");

        iconBtn->setDefaultPixmap(PIXMAP_DECK_96);
        iconBtn->setDefaultSize(96);

        frontPolicyCombo->addItem(STR_CONFIG_DECK_POLICY_ACCEPT_RICH, DeckFormat::AcceptRich);
        frontPolicyCombo->addItem(STR_CONFIG_DECK_POLICY_ACCEPT_PLAIN , DeckFormat::AcceptPlain);
        
        backPolicyCombo->addItem(STR_CONFIG_DECK_POLICY_ACCEPT_RICH, DeckFormat::AcceptRich);
        backPolicyCombo->addItem(STR_CONFIG_DECK_POLICY_ACCEPT_PLAIN , DeckFormat::AcceptPlain);
        
        editLayout->addWidget(iconBtn           ,0,0,2,1, Qt::AlignTop);
        editLayout->addWidget(nameEdit          ,0,1,1,1);
        editLayout->addWidget(descEdit          ,1,1,1,1);
        editLayout->addItem  (hSpacer()         ,2,0,1,2);
        editLayout->addWidget(authorLabel       ,3,0,1,1);
        editLayout->addWidget(authorEdit        ,3,1,1,1);
        editLayout->addWidget(tagsLabel         ,4,0,1,1);
        editLayout->addWidget(tagsEdit          ,4,1,1,1);
        editLayout->addWidget(tagTipLabel       ,5,1,1,1);
        editLayout->addWidget(createdLabel      ,6,0,1,1);
        editLayout->addWidget(createdEdit       ,6,1,1,1);
        editLayout->addWidget(updatedLabel      ,7,0,1,1);
        editLayout->addWidget(updatedEdit       ,7,1,1,1);
        editLayout->addWidget(guidLabel         ,8,0,1,1);
        editLayout->addWidget(guidEdit          ,8,1,1,1);
        editLayout->addWidget(frontPolicyLabel  ,9,0,1,1);
        editLayout->addWidget(frontPolicyCombo  ,9,1,1,1);
        editLayout->addWidget(backPolicyLabel   ,10,0,1,1);
        editLayout->addWidget(backPolicyCombo   ,10,1,1,1);
        editLayout->addWidget(formatLabel       ,11,0,1,1);
        editLayout->addWidget(formatLink        ,11,1,1,1);
        ///editLayout->addItem  (vSpacer()     ,12,0,1,2);

        switch(mode) {
        case View:
            nameEdit->setReadOnly(true);
            descEdit->setReadOnly(true);
            authorEdit->setReadOnly(true);
            tagsEdit->setReadOnly(true);
            iconBtn->setReadOnly(true);
            frontPolicyLabel->hide();
            frontPolicyCombo->hide();
            backPolicyLabel->hide();
            backPolicyCombo->hide();
            formatLabel->hide();
            formatLink->hide();

            setWindowTitle(STR_DIALOG_TITLE_VIEW_DECK);
            break;

        case Add:
            createdLabel->hide();
            createdEdit->hide();
            updatedLabel->hide();
            updatedEdit->hide();
            guidLabel->hide();
            guidEdit->hide();

            setWindowTitle(STR_DIALOG_TITLE_ADD_DECK);
            break;

        case Edit:
            setWindowTitle(STR_DIALOG_TITLE_EDIT_DECK);
            break;
        }

        createdEdit->setDisabled(true);
        updatedEdit->setDisabled(true);
        guidEdit->setDisabled(true);
	}

	//footerLayout
	{
        QPushButton *btnExit = new QPushButton(ICON_EXIT, STR_NOPE);
		QPushButton *btnSave = new QPushButton(ICON_SAVE, STR_DECK_SAVE);

        btnExit->setToolTip(STR_EXIT_DIALOG_TIP);
        btnSave->setToolTip(STR_DECK_SAVE_TIP);
		
        connect(btnExit, SIGNAL(clicked()), this, SLOT(reject()));
		connect(btnSave, SIGNAL(clicked()), this, SLOT(onSave()));
		
		btnSave->setDefault(true);

        footerLayout->addItem(hSpacer());
		footerLayout->addWidget(btnSave);
        footerLayout->addWidget(btnExit);

        switch(mode) {
        case View:
            btnSave->hide();
            break;
        }
	}

	mainLayout->addLayout(editLayout);
    mainLayout->addWidget(hLine());
	mainLayout->addLayout(footerLayout);

    //setFixedHeight(140);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
	setLayout(mainLayout);
}

void DeckDialog::setDeck(Deck *_deck)
{
    deck = _deck;

    iconBtn->setPixmap(deck->getPixmap());
    nameEdit->setText(deck->getName());
    descEdit->setPlainText(deck->getDesc());
    authorEdit->setText(deck->getAuthor());
    tagsEdit->setText(deck->getTags());
    guidEdit->setText(deck->getGuid().toString());
    createdEdit->setText(deck->getCreatedTime().toString());
    updatedEdit->setText(deck->getUpdatedTime().toString());

    frontPolicyCombo->setCurrentIndex( (int) deck->getFormat().frontEditorPolicy );
    backPolicyCombo->setCurrentIndex ( (int) deck->getFormat().backEditorPolicy  );
}

void DeckDialog::onSave()
{
    deck->setName(nameEdit->text().simplified());
    deck->setDesc(descEdit->toPlainText().simplified());
    deck->setAuthor(authorEdit->text().simplified());
    deck->setTags(tagsEdit->text().simplified());
    deck->setPixmap(iconBtn->getPixmap());

    deck->getFormat().frontEditorPolicy = (DeckFormat::EditorPolicy) frontPolicyCombo->currentIndex();
    deck->getFormat().backEditorPolicy  = (DeckFormat::EditorPolicy) backPolicyCombo->currentIndex();

    deck->saveDeck();

	accept();
}

void DeckDialog::onChangeFormat()
{
    CardDialog *dlg = new CardDialog(CardDialog::Format, this);

    DeckFormat format = deck->getFormat();

    dlg->setFormat(format);

    if(dlg->exec()==CardDialog::Accepted) {
        dlg->getFormat(format);

        deck->setFormat(format);
    }
}
