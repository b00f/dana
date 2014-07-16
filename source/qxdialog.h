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

#ifndef __QXDIALOG_H
#define __QXDIALOG_H

#include <QtGui>
#include <QtDebug>
#include <QtWidgets>

class QxDialog 
    : public QDialog
{
    Q_OBJECT

public:
    explicit QxDialog(QString name, QWidget *parent = 0);

    QVariant getSetting(const QString &key);
    void setSetting(const QString &key, const QVariant &value);
    void setWindowTitle(const QString &caption);

protected slots:
    void onFinish(int result);

protected:    
    virtual void setupView()=0;
    QWidget *hLine();
    QWidget *vLine();
    QWidget *vLine2();
    QLayoutItem *hSpacer();
    QLayoutItem *vSpacer();

    QString name;
};

#endif // __QXDIALOG_H