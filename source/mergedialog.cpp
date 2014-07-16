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

#include "mergedialog.h"
#include "decklist.h"
#include "qxmessagebox.h"
#include "constants.h"
#include "deck.h"


#define SETTING_MERGE_OPTION    "merge_option"

MergeDialog::MergeDialog(QWidget *parent)
    : QxDialog("merge_dialog", parent)
    , dstDeck(0)
    , srcDeck(0)
{
    setupView();
}

void MergeDialog::setupView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *mergeLayout  = new QVBoxLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;
    
    srcWidget = new DeckListWidget;
    dstWidget = new DeckListWidget;

    srcWidget->setDisabled(true);
    dstWidget->setDisabled(true);

    QLabel *label1 = new QLabel(STR_MERGE_SOURCE_DECK_LABLE);
    QLabel *label2 = new QLabel(STR_MERGE_DEST_DECK_LABLE);
    QGroupBox *optionBox = new QGroupBox(STR_MERGE_GROUP_CONFLICT);

    optionAcceptSource = new QRadioButton(STR_MERGE_CONFLICT_OPTION_SOURCE);
    optionAcceptDestination = new QRadioButton(STR_MERGE_CONFLICT_OPTION_DEST);
    optionAutoMerge = new QRadioButton(STR_MERGE_CONFLICT_OPTION_AUTO);

    QVBoxLayout *optionLayout = new QVBoxLayout;
    optionLayout->addWidget(optionAcceptSource);
    optionLayout->addWidget(optionAcceptDestination);
    optionLayout->addWidget(optionAutoMerge);
    optionBox->setLayout(optionLayout);

    mergeLayout->addWidget(label1);
    mergeLayout->addWidget(srcWidget);
    mergeLayout->addWidget(label2);
    mergeLayout->addWidget(dstWidget);
    mergeLayout->addWidget(optionBox);
    mergeLayout->addStretch();

    //footerLayout
    {
        QPushButton *btnCancel = new QPushButton(ICON_EXIT, STR_NOPE);
        QPushButton *btnMerge = new QPushButton(ICON_DECK_MERGE, STR_MERGE);

        connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
        connect(btnMerge, SIGNAL(clicked()), this, SLOT(onMerge()));

        btnMerge->setDefault(true);

        footerLayout->addItem(hSpacer());
        footerLayout->addWidget(btnMerge);
        footerLayout->addWidget(btnCancel);
    }

    mainLayout->addLayout(mergeLayout);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);

    setOption(getSetting(SETTING_MERGE_OPTION).toInt());

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinish(int)));

    setWindowTitle(STR_DIALOG_TITLE_MERGE);
}

void MergeDialog::onFinish(int result)
{
    Q_UNUSED(result)

    setSetting(SETTING_MERGE_OPTION, getOption());
}

void MergeDialog::setDecks(Deck *src, Deck *dst)
{
    srcDeck = src;
    dstDeck = dst;

    srcWidget->addDeck(srcDeck);
    dstWidget ->addDeck(dstDeck);

    int height = srcWidget->getRowHeight();
    srcWidget->setFixedHeight(height);
    srcWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    dstWidget->setFixedHeight(height);
    dstWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void MergeDialog::onMerge()
{
    accept();
}

int MergeDialog::getOption()
{
    if(optionAcceptSource->isChecked())
        return Deck::AcceptSource;

    if(optionAcceptDestination->isChecked())
        return Deck::AcceptTarget;

    if(optionAutoMerge->isChecked())
        return Deck::AutoMerge;

    return Deck::AutoMerge;
}

void MergeDialog::setOption(int option)
{
    switch(option)
    {
    case Deck::AcceptSource:
        optionAcceptSource->setChecked(true);
        break;

    case Deck::AcceptTarget:
        optionAcceptDestination->setChecked(true);
        break;

    //case AutoMerge:
    default:
        optionAutoMerge->setChecked(true);
        break;
    }
}
