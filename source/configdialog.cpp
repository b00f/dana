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

#include "configdialog.h"
#include "configpages.h"
#include "constants.h"

#include <QtWidgets>

ConfigDialog::ConfigDialog(QWidget *parent)
    : QxDialog("config_dialog", parent)
{
    setupView();
}

void ConfigDialog::setupView()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *horizontalLayout = new QHBoxLayout;    
    QHBoxLayout *footerLayout = new QHBoxLayout;

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::ListMode);
    contentsWidget->setIconSize(QSize(24, 24));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setMinimumWidth(96);
    contentsWidget->setSpacing(2);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new ConfigGeneralPage);
    pagesWidget->addWidget(new ConfigDeckPage);
    pagesWidget->addWidget(new ConfigNetwordPage);

    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget);

    //footerLayout
    {
        QPushButton *btnCancel = new QPushButton(QIcon(":/images/exit.png"), tr(""));
        QPushButton *btnSave = new QPushButton(QIcon(":/images/save.png"), tr("&Save"));

        connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
        connect(btnSave, SIGNAL(clicked()), this, SLOT(onSave()));

        btnSave->setDefault(true);

        footerLayout->addItem(hSpacer());
        footerLayout->addWidget(btnSave);
        footerLayout->addWidget(btnCancel);
    }

    mainLayout->addLayout(horizontalLayout);
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);

    setupIcons();
    contentsWidget->setCurrentRow(0);

    setWindowTitle(STR_DIALOG_TITLE_CONFIG);
}

void ConfigDialog::setupIcons()
{
    QListWidgetItem *generalButton = new QListWidgetItem(contentsWidget);
    generalButton->setIcon(ICON_CONFIG_GENERAL);
    generalButton->setText(STR_CONFIG_LIST_GENERAL);
    
    QListWidgetItem *deckButton = new QListWidgetItem(contentsWidget);
    deckButton->setIcon(ICON_CONFIG_DECK);
    deckButton->setText(STR_CONFIG_LIST_DECK);

    QListWidgetItem *networkButton = new QListWidgetItem(contentsWidget);
    networkButton->setIcon(ICON_CONFIG_NETWORK);
    networkButton->setText(STR_CONFIG_LIST_NETWORK);
    
    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void ConfigDialog::onSave()
{
    int count = pagesWidget->count();

    for(int index =0; index < count; index++) {
        ((ConfigPage *)pagesWidget->widget(index))
            ->save();
    }

    accept();
}