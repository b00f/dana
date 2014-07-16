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

#ifndef __CONFIGDIALOG_H
#define __CONFIGDIALOG_H

#include "qxdialog.h"

class ConfigDialog : public QxDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void onSave();

private:
    void setupView();
    void setupIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif // __CONFIGDIALOG_H
