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

#ifndef __CHILDWINDOW_H
#define __CHILDWINDOW_H

#include <QtGui>
#include <QtDebug>
#include <QtWidgets>

class ChildWindow 
    : public QWidget
{
    Q_OBJECT
public:
    explicit ChildWindow(QMainWindow *parent = 0);

    virtual void setupMenu();

signals:
    void exit();
    void showAbout();
    void checkUpdate();
    
protected slots:
    void showConfig();
    void onSupport();
    void onReportBug();
    
protected:
    virtual void setupActions();
    virtual void setupToolbar()=0;
    virtual void setupView();
    virtual void setupContextMenu()=0;

protected:
    QLabel *title;
    QToolBar *toolbar;
    QLayout *mainLayout;


    QMenuBar *mainMenu;

    QAction *actAbout;
    QAction *actSupport;
    QAction *actReport;
    QAction *actQuit;
    QAction *actConfig;
    QAction *actUpdateCheck;
};

#endif // __CHILDWINDOW_H
