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

#ifndef __DESKWINDOW_H
#define __DESKWINDOW_H

#include "decklist.h"
#include "childwindow.h"
#include "decklistwidget.h"

class DeskWindow 
    : public ChildWindow
{
    Q_OBJECT

public:
    explicit DeskWindow(QMainWindow *parent = 0);

    void setDeckList(DeckList* _deckList);

    void openDeckByName(QString deckName);
    
signals:
    void openDeck(Deck *deck);

private slots:
    void onCreateDeck();
    void onImportDeck();
    void onEditDeck();
    void onDeleteDeck();
    void onExportDeck();
    void onSelectionChang();
    void onOpenDeck();
    void onMergeDeck();
    void onDownloadDeck();
    void onUploadDeck();
    
    void importDeck(const QString &fileName);
    void exportDeck(Deck *deck, const QString &fileName);
    void mergeDecks(Deck* src, Deck* dst);

private:
    void setupToolbar();
    void setupActions();
    void setupView();
    void setupMenu();
    void setupContextMenu();

    void updateView();

    Deck *getDeckByName(const QString &deckName);

private:
    QAction *actOpen,
            *actCreate,
            *actMerge,
            *actImport,
            *actExport,
            *actDownload,
            *actUpload,
            *actEdit,
            *actDelete;

    DeckListWidget *deckListWidget;
    DeckList *deckList;
};

#endif // __DESKWINDOW_H