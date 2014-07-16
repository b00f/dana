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

#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QItemSelection>
#include <QProgressBar>
#include <QtGui>

#include "progressdialog.h"
#include "childwindow.h"

class Deck;
class DeckList;
class MainWindow 
    : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void onOpenDeck(Deck *deck);
	void onOpenDesk();
	void onActivateTrayIcon(QSystemTrayIcon::ActivationReason reason);
	void quitApp();
    void showAbout();
    void onCheckUpdate();
    void updateChecked(const QString& result);
	void onMessageReceiveFromOtherInst(const QString &msg);
    void showQuickQuery();
    void onQuickQuery(bool running);

private:
	
protected:
    void closeEvent(QCloseEvent *event);
    void createViewWidgets();
private:
    QStackedLayout *stackedLayout;
    ChildWindow *deckWindow;
    ChildWindow *deskWindow;

    QAction *actQuery; /// show Quick Query dialog
	QAction *actRestore;
    QAction *actAbout;
    QAction *actQuit;

	QSystemTrayIcon *trayIcon;

    ProgressDialog *progressDialog;
    QProgressBar *progressBar; /// status bar
    DeckList *deckList;
};

#endif // __MAINWINDOW_H