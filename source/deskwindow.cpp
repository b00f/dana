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

#include "deskwindow.h"
#include "downloaddialog.h"
#include "uploaddialog.h"
#include "networkmanager.h"
#include "logindialog.h"
#include "deckdialog.h"
#include "qxfiledialog.h"
#include "qxsettings.h"
#include "mergedialog.h"
#include "progressdialog.h"
#include "decklist.h"
#include "tempdeck.h"
#include "mydeck.h"
#include "qxmessagebox.h"
#include "constants.h"


DeskWindow::DeskWindow(QMainWindow *parent)
    : ChildWindow(parent)
{
    deckList = 0;

    setupView();
    setupActions();
    setupToolbar();
    setupMenu();
    setupContextMenu();    
}

void DeskWindow::setupView()
{
    deckListWidget = new DeckListWidget(this);
    deckListWidget->hideSearchBox();

    mainLayout->addWidget(deckListWidget);

    title->setText(STR_DECKS);

    connect(deckListWidget, SIGNAL(selectionChanged()), this, SLOT(onSelectionChang()));
    connect(deckListWidget, SIGNAL(activated()), this, SLOT(onOpenDeck()));
}

void DeskWindow::setupToolbar()
{
    toolbar->addAction(actDownload);
    toolbar->addAction(actMerge);
    toolbar->addAction(actImport);
    toolbar->addAction(actExport);
    toolbar->addSeparator();
    toolbar->addAction(actCreate);
    toolbar->addAction(actEdit);
    ///toolbar->addAction(actDelete);
    toolbar->addSeparator();
    toolbar->addAction(actAbout);
}

void DeskWindow::setupMenu()
{
    mainMenu->clear();

    /// Deck Menu
    QMenu *deckMenu = mainMenu->addMenu(STR_MENU_DECK);
    deckMenu->addAction(actOpen);
    deckMenu->addAction(actEdit);
    deckMenu->addAction(actDelete);    
    deckMenu->addSeparator();
    deckMenu->addAction(actQuit);

    /// Action Menu
    QMenu *actionMenu = mainMenu->addMenu(STR_MENU_ACTION);
    actionMenu->addAction(actCreate);
    actionMenu->addAction(actImport);
    actionMenu->addAction(actExport);
    actionMenu->addAction(actMerge);
    actionMenu->addSeparator();
    actionMenu->addAction(actDownload);
    actionMenu->addAction(actUpload);
    actionMenu->addSeparator();
    actionMenu->addAction(actConfig);

    ChildWindow::setupMenu();
}

void DeskWindow::setupContextMenu()
{
    QMenu *contextMent = new QMenu(this);
    contextMent->addAction(actOpen);
    contextMent->addAction(actExport);
    contextMent->addAction(actUpload);
    contextMent->addAction(actMerge);
    contextMent->addSeparator();
    contextMent->addAction(actEdit);
    contextMent->addAction(actDelete);

    deckListWidget->setContextMenu(contextMent);
}

void DeskWindow::setupActions()
{
    actOpen = new QAction(ICON_DECK_OPEN, STR_ACTION_DECK_OPEN, this);
    actOpen->setShortcut(QKeySequence::Open);
    actOpen->setStatusTip(STR_ACTION_DECK_OPEN_TIP);
    actOpen->setDisabled(true);
    connect(actOpen, SIGNAL(triggered()), this, SLOT(onOpenDeck()));

    actCreate = new QAction(ICON_DECK_CREATE, STR_ACTION_DECK_CREATE, this);
    actCreate->setShortcut(QKeySequence("Insert"));
    actCreate->setStatusTip(STR_ACTION_DECK_CREATE_TIP);
    connect(actCreate, SIGNAL(triggered()), this, SLOT(onCreateDeck()));

    actMerge = new QAction(ICON_DECK_MERGE, STR_ACTION_DECK_MERGE, this);
    actMerge->setStatusTip(STR_ACTION_DECK_MERGE_TIP);
    actMerge->setDisabled(true);
    connect(actMerge, SIGNAL(triggered()), this, SLOT(onMergeDeck()));

    actImport = new QAction(ICON_DECK_IMPORT, STR_ACTION_DECK_IMPORT, this);
    actImport->setShortcut(QKeySequence::Open);
    actImport->setStatusTip(STR_ACTION_DECK_IMPORT_TIP);
    connect(actImport, SIGNAL(triggered()), this, SLOT(onImportDeck()));

    actExport = new QAction(ICON_DECK_EXPORT, STR_ACTION_DECK_EXPORT, this);
    actExport->setStatusTip(STR_ACTION_DECK_EXPORT_TIP);
    actExport->setShortcut(QKeySequence("Ctrl+E"));
    actExport->setDisabled(true);
    connect(actExport, SIGNAL(triggered()), this, SLOT(onExportDeck()));

    actDownload = new QAction(ICON_DECK_DOWNLOAD, STR_ACTION_DECK_DOWNLOAD, this);
    actDownload->setStatusTip(STR_ACTION_DECK_DOWNLOAD_TIP);
    connect(actDownload, SIGNAL(triggered()), this, SLOT(onDownloadDeck()));

    actUpload = new QAction(ICON_DECK_UPLOAD, STR_ACTION_DECK_UPLOAD, this);
    actUpload->setStatusTip(STR_ACTION_DECK_UPLOAD_TIP);
    actUpload->setDisabled(true);
    connect(actUpload, SIGNAL(triggered()), this, SLOT(onUploadDeck()));

    actEdit = new QAction(ICON_DECK_EDIT, STR_ACTION_DECK_EDIT, this);
    actEdit->setStatusTip(STR_ACTION_DECK_EDIT_TIP);
    actEdit->setDisabled(true);
    connect(actEdit, SIGNAL(triggered()), this, SLOT(onEditDeck()));

    actDelete = new QAction(ICON_DECK_REMOVE, STR_ACTION_DECK_REMOVE, this);
    actDelete->setShortcut(QKeySequence::Delete);
    actDelete->setStatusTip(STR_ACTION_DECK_REMOVE_TIP);
    actDelete->setDisabled(true);
    connect(actDelete, SIGNAL(triggered()), this, SLOT(onDeleteDeck()));
    
    ChildWindow::setupActions();
}

void DeskWindow::setDeckList(DeckList* _deckList)
{
    deckList = _deckList;

    updateView();
}

void DeskWindow::updateView()
{
    int selIndex = 0;

    deckListWidget->getSelectedDeck(&selIndex);
    deckListWidget->setDeckList(deckList);
    deckListWidget->selectRow(selIndex);
}

void DeskWindow::onCreateDeck()
{
    Deck *deck = new MyDeck();

    QString new_name = QString(STR_DECK_NEW);
    
    deck->setName(new_name);
        
    DeckDialog dlg(DeckDialog::Add, this);

    dlg.setDeck(deck);

    if(dlg.exec()==QDialog::Accepted) {
        deckList->addDeck(deck);

        updateView();
    } else {
        zap(deck);
    }
}

void DeskWindow::onOpenDeck()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;
    
    if(deck->openDeck())
    {
        emit openDeck(deck);
    }
}

void DeskWindow::onEditDeck()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;

    DeckDialog dlg(DeckDialog::Edit, this);
    
    dlg.setDeck(deck);

    if(dlg.exec()==QDialog::Accepted) {
        updateView();
    }
}

void DeskWindow::onDeleteDeck()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;

    if( QxMessageBox::question(this, WNG_REMOVE_DECK.arg(deck->getName()), WNG_REMOVE_DECK_TITLE) == 
        QxMessageBox::Yes) {
        deckList->removeOneDeck(deck);
        zap(deck);
        updateView();
    }
}

void DeskWindow::onImportDeck()
{
    QString fileName = QxFileDialog(this).getOpenDeckName();

    if (!fileName.isEmpty()) {
       importDeck(fileName);
    }
}

void DeskWindow::onMergeDeck()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;

    QString fileName = QxFileDialog(this).getOpenDeckName();

    if (!fileName.isEmpty()) {
        Deck *tempDeck = new TempDeck;

        if(!tempDeck->importDeck(fileName)) {
            QxMessageBox::critical(this, ERR_MSG_DECK_IMPORT_FAILD);
        } else {
            mergeDecks(deck, tempDeck);
        }

        delete tempDeck;
    }
}

void DeskWindow::onExportDeck()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return;

    QString fileName = QxFileDialog(this).getSaveDeckName();

    if (!fileName.isEmpty()) {
        exportDeck(deck, fileName);
    }
}

void DeskWindow::mergeDecks(Deck* src, Deck* dst)
{
    MergeDialog dlg(this);
    dlg.setDecks(src, dst);

    if(dlg.exec() == QDialog::Accepted) {
        int added = 0;
        src->Merge(dst, dlg.getOption(), &added);

        QxMessageBox::information(this, INFO_MSG_DECK_MERGE_STATE.arg(added));
    }
}

void DeskWindow::importDeck(const QString &fileName)
{
    Deck *tempDeck = new TempDeck;

    if(!tempDeck->importDeck(fileName)) {
        QxMessageBox::critical(this, ERR_MSG_DECK_IMPORT_FAILD);
    } else {
        Deck* deck = deckList->findDeckById(tempDeck->getGuid());

        if(deck) {
            mergeDecks(deck, tempDeck);
        } else {
            deck = new MyDeck;
            /// to store in DB
            deck->saveDeck();
            deck->Merge(tempDeck);

            deckList->addDeck(deck);
        }
    }

    updateView();

    /// memory leak 
    delete tempDeck;
}

void DeskWindow::exportDeck(Deck *deck, const QString &fileName)
{
    if(!deck->exportDeck(fileName)) {
        QxMessageBox::critical(this, ERR_MSG_DECK_EXPORT_FAILD);
    }
}

void DeskWindow::onSelectionChang()
{
    Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck) {
        actOpen->setEnabled(false);
        actEdit->setEnabled(false);
        actDelete->setEnabled(false);
        actExport->setEnabled(false);
        actMerge->setEnabled(false);
        actUpload->setEnabled(false);
    } else {
        actOpen->setEnabled(true);
        actEdit->setEnabled(true);
        actDelete->setEnabled(true);
        actExport->setEnabled(true);
        actMerge->setEnabled(true);
        actUpload->setEnabled(true);
    }
}

void DeskWindow::openDeckByName(QString deckName)
{
    Deck *deck = getDeckByName(deckName);

    if(deck && deck->openDeck())
    {
        emit openDeck(deck);
    }
}

Deck *DeskWindow::getDeckByName(const QString &deckName)
{
    Deck *deck = 0;
    int count = deckList->getCount();

    for(int i=0;i<count;i++) {
        deck = deckList->getDeckAt(i);
        if(QString::compare(deck->getName(), deckName,
                            Qt::CaseInsensitive)==0) {

            return deck;
        }
    }

    return 0;
}

void DeskWindow::onDownloadDeck()
{
    DownloadDialog dlg(this);

    connect(&dlg, SIGNAL(downloaded(const QString &)), this, SLOT(importDeck(const QString &)));

    dlg.exec();
}

void DeskWindow::onUploadDeck()
{
     Deck *deck = deckListWidget->getSelectedDeck();

    if(!deck)
        return; 

    UploadDialog dlg(this);

    dlg.uploadDeck(deck);
}