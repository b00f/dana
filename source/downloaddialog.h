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

#ifndef __DOWNLOADDIALOG_H
#define __DOWNLOADDIALOG_H

#include "qxdialog.h"
#include "decklist.h"
#include "combolabel.h"
#include "decklistwidget.h"
#include "progressdialog.h"

#include <QNetworkReply>

class DownloadDialog 
    : public QxDialog
{
    Q_OBJECT

public:
    explicit DownloadDialog(QWidget *parent = 0);

private slots:
    void onDownload();
    void onProperties();
    void onSelectionChang();
    void onFailure(const QString& error);
    void onVote(Deck* deck, int rating);
    void onChangeSortRole(int index);
    void onChangeViewOption(int index);
    void onFinishDownloading(const QString& fileName);
    void loadList(const QString& xml);
    void updateProgress(qint64 finished, qint64 total);

signals:
    void downloaded(const QString &);

private:
    void setupView();
    void setupActions();
    void setupContextMenu();

    bool loadList();


private:
    ComboLabel* comboSort;
    ComboLabel* comboViewOption;
    QPushButton *btnDownload;
    QLabel *lblError;

    QAction *actDownload;
    QAction *actProperties;

    DeckListWidget *deckListWidget;
    DeckList *deckList;
    ProgressDialog *progressDialog;
};

#endif // __DOWNLOADDIALOG_H