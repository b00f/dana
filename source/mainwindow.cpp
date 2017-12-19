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

#include "mainwindow.h"
#include "deskwindow.h"
#include "aboutdialog.h"
#include "deckwindow.h"
#include "qxsettings.h"
#include "qxmessagebox.h"
#include "databasemanager.h"
#include "networkmanager.h"
#include "preferences.h"
#include "constants.h"
#include "decklist.h"
#include "deck.h"
#include "constants.h"

#ifdef _DEBUG
    //// just for memory leak detection
    ////#include <vld.h>
#endif

#define SETTING_GROUP_NAME              "main_window"
#define SETTING_KEY_DECK_NAME           "deck_name"
#define SETTING_KEY_GEOMETRY            "geometry"

MainWindow::MainWindow()
{
    QCoreApplication::setOrganizationName(APP_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    QIcon appIcon;

    appIcon.addPixmap(PIXMAP_DANA_16);
    appIcon.addPixmap(PIXMAP_DANA_24);
    appIcon.addPixmap(PIXMAP_DANA_32);
    appIcon.addPixmap(PIXMAP_DANA_48);
    appIcon.addPixmap(PIXMAP_DANA_64);
    appIcon.addPixmap(PIXMAP_DANA_72);
    appIcon.addPixmap(PIXMAP_DANA_96);

    setWindowIcon(appIcon);

    Preferences::GetInstance();
    NetworkManager::GetInstance();
    DatabaseManager::GetInstance();

    /// --- load deck list
    deckList = new DeckList(this);
    DatabaseManager::GetInstance()->loadDeckList(deckList);

    stackedLayout = new QStackedLayout;
    deckWindow = new DeckWindow(this);
    deskWindow = new DeskWindow(this);

    ((DeskWindow *)deskWindow)->setDeckList(deckList);

    QWidget *centralWidget = new QWidget(this);

    centralWidget->setLayout(stackedLayout);
    setCentralWidget(centralWidget);

    stackedLayout->addWidget(deckWindow);
    stackedLayout->addWidget(deskWindow);

    setWindowTitle(APP_TITLE);

    connect(deckWindow, SIGNAL(openDesk()), this, SLOT(onOpenDesk()));
    connect(deckWindow, SIGNAL(quickQuery(bool)), this, SLOT(onQuickQuery(bool)));
    connect(deskWindow, SIGNAL(openDeck(Deck*)), this, SLOT(onOpenDeck(Deck*)));

    connect(deckWindow, SIGNAL(showAbout()), this, SLOT(showAbout()));
    connect(deskWindow, SIGNAL(showAbout()), this, SLOT(showAbout()));

    connect(deckWindow, SIGNAL(checkUpdate()), this, SLOT(onCheckUpdate()));
    connect(deskWindow, SIGNAL(checkUpdate()), this, SLOT(onCheckUpdate()));

    connect(deckWindow, SIGNAL(exit()), this, SLOT(quitApp()));
    connect(deskWindow, SIGNAL(exit()), this, SLOT(quitApp()));

    stackedLayout->setCurrentWidget(deskWindow);

	/// ----------------------
	/// create tray icon
	actRestore = new QAction(STR_ACTION_RESTORE, this);
    actRestore->setStatusTip(STR_ACTION_RESTORE_TIP);
	connect(actRestore, SIGNAL(triggered()), this, SLOT(showNormal()));

	actQuit = new QAction(STR_ACTION_QUIT, this);
    actQuit->setStatusTip(STR_ACTION_QUIT_TIP);
    actQuit->setShortcut(QKeySequence("Ctrl+Q"));
	connect(actQuit, SIGNAL(triggered()), this, SLOT(quitApp()));

    actAbout = new QAction(STR_ACTION_ABOUT, this);
    actAbout->setStatusTip(STR_ACTION_ABOUT_TIP);
    actAbout->setShortcut(QKeySequence("F1"));
    connect(actAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    QMenu *trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(actRestore);
    trayIconMenu->addAction(actAbout);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(actQuit);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(appIcon);

	trayIcon->show();

	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
         this, SLOT(onActivateTrayIcon(QSystemTrayIcon::ActivationReason)));

    QString lastDeckName = QxSettings::getSetting(SETTING_KEY_DECK_NAME, SETTING_GROUP_NAME).toString();
    ((DeskWindow *)deskWindow)->openDeckByName(lastDeckName);

    restoreGeometry(QxSettings::getSetting(SETTING_KEY_GEOMETRY, SETTING_GROUP_NAME).toByteArray());

   //// statusBar()->showMessage(STR_STATUS_READY);

    Preferences *preferences = Preferences::GetInstance();
    if(preferences->isCheckUpdate()) {
        onCheckUpdate();
    }
}

void MainWindow::quitApp()
{
    deckList->clear();

    QxSettings::setSetting(SETTING_KEY_GEOMETRY, SETTING_GROUP_NAME, saveGeometry());

    DatabaseManager::DestroyInstance();
    NetworkManager::DestroyInstance();
    Preferences::DestroyInstance();

    QCoreApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

void MainWindow::onOpenDeck(Deck *deck)
{
    ((DeckWindow *)deckWindow)->setDeck((MyDeck*)deck);

    deckWindow->setupMenu();

    stackedLayout->setCurrentWidget(deckWindow);

    QxSettings::setSetting(SETTING_KEY_DECK_NAME, SETTING_GROUP_NAME, deck->getName());
}

void MainWindow::onOpenDesk()
{
    deskWindow->setupMenu();

    stackedLayout->setCurrentWidget(deskWindow);

    QxSettings::setSetting(SETTING_KEY_DECK_NAME, SETTING_GROUP_NAME, "");
}

void MainWindow::onActivateTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
        showNormal();
        break;

    // mac build
    default:
        break;
    }
}

void MainWindow::onMessageReceiveFromOtherInst(const QString &)
{
	show();

	//QApplication::postEvent(this, new QEvent(Event_Main_Raise));
}

void MainWindow::showAbout()
{
    AboutDialog *aboutDlg = new AboutDialog(this);

    aboutDlg->exec();
}

void MainWindow::onCheckUpdate()
{
    NetworkManager *netMan = NetworkManager::GetInstance();

    connect(netMan, SIGNAL(succeed(const QString&)), this, SLOT(updateChecked(const QString&)));

    netMan->checkUpdate();
}

void MainWindow::updateChecked(const QString& result)
{
    if(result.isEmpty())
        return;

    if( QxMessageBox::question(this, result, STR_UPDATE_DANA) ==
        QxMessageBox::No) {
            Preferences *preferences = Preferences::GetInstance();

            preferences->setCheckUpdate(false); /// don't check for update again
            return;
    }

    QDesktopServices::openUrl(
        QUrl("http://dana-box.com/download.php", QUrl::TolerantMode));
}

void MainWindow::onQuickQuery(bool running)
{
    if(running)
        hide();
    else
        show();
}
