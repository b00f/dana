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

#include "downloaddialog.h"
#include "deckproxymodel.h"
#include "networkmanager.h"
#include "deckdialog.h"
#include "decklist.h"
#include "logindialog.h"
#include "ideck.h"
#include "constants.h"

#include <QDomDocument>
#include <QDomElement>
#include <QNetworkReply>

#define SETTING_SORT_ROLE_INDEX     "sort_role_index"
#define SETTING_VIEW_OPTION_INDEX   "view_option_index"


DownloadDialog::DownloadDialog(QWidget *parent)
    : QxDialog("download_dialog", parent)
{    
    setupView();
    setupActions();
    setupContextMenu();

    progressDialog = new ProgressDialog(this);
    deckList = new DeckList(this);

    NetworkManager *netMan = NetworkManager::GetInstance();
    
    connect(netMan, SIGNAL(succeed(const QString&)), this, SLOT(loadList(const QString&)));
    connect(netMan, SIGNAL(failed(const QString&)), this, SLOT(onFailure(const QString&)));

    netMan->getDeckList();
}

void DownloadDialog::setupView()
{
    deckListWidget = new DeckListWidget;
    btnDownload = new QPushButton(ICON_DECK_DOWNLOAD, STR_ACTION_DOWNLOAD);

    deckListWidget->hideSearchBox(false);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *filterLayout = new QHBoxLayout;
    QHBoxLayout *footerLayout = new QHBoxLayout;

    //footerLayout
    {
        QPushButton *btnCancel = new QPushButton(ICON_EXIT, STR_NOPE);

        connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
        connect(btnDownload, SIGNAL(clicked()), this, SLOT(onDownload()));

        btnDownload->setDefault(true);
        btnDownload->setEnabled(false);

        footerLayout->addItem(hSpacer());
        footerLayout->addWidget(btnDownload);
        footerLayout->addWidget(btnCancel);
    }
    
    comboSort = new ComboLabel(ICON_SORT);
    comboViewOption = new ComboLabel(ICON_VIEW_OPTIONS);
    
    comboSort->addItem(STR_DOWNLOAD_DIALOG_SORT_BY_DATE       , DeckListDataModel::CreatedTimeRole );
    comboSort->addItem(STR_DOWNLOAD_DIALOG_SORT_BY_NAME       , DeckListDataModel::NameRole        );
    comboSort->addItem(STR_DOWNLOAD_DIALOG_SORT_BY_CARD_NUMBER, DeckListDataModel::CardNumberRole  );
    comboSort->addItem(STR_DOWNLOAD_DIALOG_SORT_BY_DOWNLOADS  , DeckListDataModel::DownloadsRole   );
    comboSort->addItem(STR_DOWNLOAD_DIALOG_SORT_BY_RATING     , DeckListDataModel::RatingRole      );

    comboViewOption->addItem(STR_DOWNLOAD_DIALOG_VIEW_OPTION_LIST,   DeckItemDelegate::ListView);
    comboViewOption->addItem(STR_DOWNLOAD_DIALOG_VIEW_OPTION_DETAIL, DeckItemDelegate::DetailView);

    filterLayout->addWidget(comboSort);
    filterLayout->addStretch();
    filterLayout->addWidget(comboViewOption);

    lblError = new QLabel;

    mainLayout->addWidget(lblError);
    mainLayout->addWidget(deckListWidget);
    mainLayout->addLayout(filterLayout);
    
    mainLayout->addWidget(hLine());
    mainLayout->addLayout(footerLayout);

    connect(deckListWidget, SIGNAL(selectionChanged()), this, SLOT(onSelectionChang()));
    connect(deckListWidget, SIGNAL(activated()), this, SLOT(onDownload()));
    connect(deckListWidget, SIGNAL(voted(Deck*, int)), this, SLOT(onVote(Deck*, int)));
    connect(comboViewOption, SIGNAL(comboIndexChanged(int)), this, SLOT(onChangeViewOption(int)));
    connect(comboSort, SIGNAL(comboIndexChanged(int)), this, SLOT(onChangeSortRole(int)));
    
    int viewOptionIndex = getSetting(SETTING_VIEW_OPTION_INDEX).toInt();
    comboViewOption->setCurrentIndex(viewOptionIndex);

    int sortRoleIndex = getSetting(SETTING_SORT_ROLE_INDEX).toInt();
    comboSort->setCurrentIndex(sortRoleIndex);

    setWindowTitle(STR_DIALOG_TITLE_DOWNLOAD);
}

void DownloadDialog::setupContextMenu()
{
    QMenu *contextMent = new QMenu;
    
    contextMent->addAction(actProperties);
    contextMent->addAction(actDownload);

    deckListWidget->setContextMenu(contextMent);
}

void DownloadDialog::setupActions()
{
    actDownload = new QAction(ICON_DECK_DOWNLOAD, STR_ACTION_DOWNLOAD, this);
    actDownload->setStatusTip(STR_ACTION_DECK_DOWNLOAD_TIP);
    connect(actDownload, SIGNAL(triggered()), this, SLOT(onDownload()));
    
    actProperties = new QAction(ICON_DECK_EDIT, STR_ACTION_DECK_PROPERTIES, this);
    actProperties->setStatusTip(STR_ACTION_DECK_PROPERTIES_TIP);
    connect(actProperties, SIGNAL(triggered()), this, SLOT(onProperties()));
}

void DownloadDialog::onFailure(const QString& error)
{
    lblError->setText(QString("<font color='red'><b> *%1</b></font>").arg(error));
}

void DownloadDialog::onDownload()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;

    btnDownload->setEnabled(false);
    progressDialog->show();

    NetworkManager *netMan = NetworkManager::GetInstance();

    connect(progressDialog, SIGNAL(canceled()), netMan, SLOT(doAbort()));
    connect(netMan, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(updateProgress(qint64, qint64))); 
    connect(netMan, SIGNAL(succeed(const QString &)), this, SLOT(onFinishDownloading(const QString &)));
    connect(netMan, SIGNAL(failed(const QString&)), this, SLOT(onFailure(const QString&)));

    netMan->downloadDeck(deck->getId());
}

void DownloadDialog::onProperties()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;

    DeckDialog dlg(DeckDialog::View, this);
    
    dlg.setDeck(deck);

    dlg.exec();
}

void DownloadDialog::onSelectionChang()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck) {
        btnDownload->setEnabled(false);
    } else {
        btnDownload->setEnabled(true);
    }
}

void DownloadDialog::loadList(const QString& xml)
{
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(xml, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qDebug() << xml;
        qDebug() << QString("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr);
        return;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName().toLower() != XML_TAG_ROOT) {
        qDebug() << "root node is mismatched.";

        return;
    }

    QDomElement nodeDecks = root.firstChildElement(XML_TAG_DECKS);
    if(nodeDecks.isNull()) {
        qDebug() << "deck node is mismatched.";

        return;
    }

    QDomNodeList nodeList = nodeDecks.childNodes();

   iDeck *deck;
   QDomNode nodeDeck;

   for(int i=0; i<nodeList.count();i++) {
       nodeDeck = nodeList.at(i);

       if(nodeDeck.isNull()) {
           qDebug() << "deck node is mismatched.";

           return;
       }

       deck = new iDeck;

       deck->openDeck(nodeDeck);

       deckList->addDeck(deck);
   }

    deckListWidget->setDeckList(deckList);

    // to set role after creating model
    onChangeSortRole  ( comboSort->currentIndex() );
    onChangeViewOption( comboViewOption->currentIndex() );
}

void DownloadDialog::onVote(Deck* deck, int rating)
{
    NetworkManager *netMan = NetworkManager::GetInstance();

    if(!netMan->isLoggedin())
    {
        LoginDialog dlg(this);
        if(dlg.exec()!=QDialog::Accepted) {
            return;
        }        
    }
    
    netMan->vote(deck->getId(), rating);

    ((iDeck *)deck)->setRating(rating);
}

void DownloadDialog::onChangeSortRole(int index)
{
    int sortRole = comboSort->itemData(index).toInt();

    deckListWidget->setSortRole(sortRole);

    setSetting(SETTING_SORT_ROLE_INDEX, index);
}

void DownloadDialog::onChangeViewOption(int index)
{
    int viewOption = comboViewOption->itemData(index).toInt();

    deckListWidget->setViewOption(viewOption);

    setSetting(SETTING_VIEW_OPTION_INDEX, index);
}

void DownloadDialog::updateProgress(qint64 finished, qint64 total)
{
    progressDialog->updateProgress(finished, total);
}

void DownloadDialog::onFinishDownloading(const QString& fileName)
{
    progressDialog->close();
    accept();

    emit downloaded(fileName);
}
