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

#include "childwindow.h"
#include "aboutdialog.h"
#include "configdialog.h"
#include "constants.h"

#include <QDesktopServices>

ChildWindow::ChildWindow(QMainWindow *parent)
    : QWidget(parent)
{
    mainMenu = parent->menuBar();

    setupView();
}

void ChildWindow::setupView()
{
    QGridLayout *gridLayout = new QGridLayout(this);

    title = new QLabel;
    toolbar = new QToolBar;
    mainLayout = new QVBoxLayout;

    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    ///title->setMaximumWidth(500);

    QSpacerItem *hSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addWidget(title     , 0, 0, 1, 1);
    gridLayout->addItem  (hSpacer   , 0, 1, 1, 1);
    gridLayout->addWidget(toolbar   , 0, 2, 1, 1);
    gridLayout->addLayout(mainLayout, 1, 0, 1, 3);

    title->setStyleSheet("QLabel{font-weight:bold;font-size:20px;color:#2A4A70;font-style:normal;}");
}

void ChildWindow::setupActions()
{
    actAbout = new QAction(ICON_ABOUT, STR_ACTION_ABOUT, this);
    actAbout->setStatusTip(STR_ACTION_ABOUT_TIP);
    actAbout->setShortcut(QKeySequence("F1"));
    connect(actAbout, SIGNAL(triggered()), this, SIGNAL(showAbout()));

    actSupport = new QAction(STR_ACTION_SUPPORT, this);
    actSupport->setStatusTip(STR_ACTION_SUPPORT_TIP);
    connect(actSupport, SIGNAL(triggered()), this, SLOT(onSupport()));

    actReport = new QAction(STR_ACTION_REPORT_BUG, this);
    actReport->setStatusTip(STR_ACTION_REPORT_BUG_TIP);
    connect(actReport, SIGNAL(triggered()), this, SLOT(onReportBug()));

    actConfig = new QAction(ICON_CONFIG, STR_ACTION_CONFIG, this);
    actConfig->setStatusTip(STR_ACTION_CONFIG_TIP);
    actConfig->setShortcut(QKeySequence("Ctrl+p"));
    connect(actConfig, SIGNAL(triggered()), this, SLOT(showConfig()));

    actUpdateCheck = new QAction(STR_ACTION_UPDATE_CHECK, this);
    actUpdateCheck->setStatusTip(STR_ACTION_UPDATE_CHECK_TIP);
    connect(actUpdateCheck, SIGNAL(triggered()), this, SIGNAL(checkUpdate()));

    actQuit = new QAction(STR_ACTION_QUIT, this);
    actQuit->setStatusTip(STR_ACTION_QUIT_TIP);
    actQuit->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actQuit, SIGNAL(triggered()), this, SIGNAL(exit()));
}


void ChildWindow::setupMenu()
{
    /// Help Menu
    QMenu *helpMenu = mainMenu->addMenu(STR_MENU_HELP);

    helpMenu->addAction(actAbout);
    helpMenu->addSeparator();
    helpMenu->addAction(actSupport);
    helpMenu->addAction(actReport);
    helpMenu->addAction(actUpdateCheck);
}

void ChildWindow::showConfig()
{
    ConfigDialog *configDlg = new ConfigDialog(this);

    configDlg->exec();
}

void ChildWindow::onSupport()
{
    QDesktopServices::openUrl(
        QUrl("http://dana-box.com/support.php", QUrl::TolerantMode));
}

void ChildWindow::onReportBug()
{
    QDesktopServices::openUrl(
        QUrl("http://dana-box.com/report_bug.php", QUrl::TolerantMode));
}
