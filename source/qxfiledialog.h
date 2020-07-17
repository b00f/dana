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

#ifndef __QXFILEDIALOG_H
#define __QXFILEDIALOG_H

#include <QFileDialog>

class QxFileDialog
    : public QFileDialog
{
    Q_OBJECT

public:
    explicit QxFileDialog(QWidget *parent = nullptr);

    QString getOpenFileName(const QString &caption = QString(),
                            const QString &filter = QString(),
                            QString *selectedFilter = 0,
                            Options options = Options());

    QString getSaveFileName(const QString &caption = QString(),
                            const QString &filter = QString(),
                            QString *selectedFilter = 0,
                            Options options = Options());

    QString getOpenDeckName();
    QString getSaveDeckName();
    QString getOpenImageName();
    QString getOpenTexName();

signals:

public slots:

};

#endif // __QXFILEDIALOG_H