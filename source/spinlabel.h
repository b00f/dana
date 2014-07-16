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

#ifndef __SPINLABEL_H
#define __SPINLABEL_H

#include "clickablelabel.h"

#include <QStackedLayout>
#include <QSpinBox>

class SpinLabel 
    : public QWidget
{
    Q_OBJECT

public:
    explicit SpinLabel(QString format = "%1", QWidget *parent = 0);

    void setSpinValue(int value);
    int getSpinValue();

    void closeEditor();

signals:
    void spinValueChanged(int);

private slots:
    void onSpinValueChanged(int value);
    void onClick();

protected:
    void focusOutEvent(QFocusEvent *);
    void focusInEvent(QFocusEvent *);

private:
    QSpinBox *spin;
    ClickableLabel *label;
	QStackedLayout *stacked;

    QString format;
};

#endif // __SPINLABEL_H