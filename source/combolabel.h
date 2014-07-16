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

#ifndef __COMBOLABEL_H
#define __COMBOLABEL_H

#include "clickablelabel.h"

#include <QStackedLayout>
#include <QComboBox>

class ComboLabel 
    : public QWidget
{
    Q_OBJECT

public:
    explicit ComboLabel(const QIcon &icon = QIcon(), bool labelToRight = false, QWidget *parent = 0);

    void addItem(const QString &text, const QVariant &userData = QVariant());

    void setCurrentIndex(int index);
    int currentIndex();

    QVariant itemData (int index, int role = Qt::UserRole) const;
    
signals:
    void comboIndexChanged(int);

private slots:
	void onComboChanged(const QString &text);
    void onClick();

protected:
    void focusOutEvent(QFocusEvent *);
    void focusInEvent(QFocusEvent *);

    void closeEditor();

private:
    QComboBox *combo;
    QHBoxLayout *labelLayout;
	ClickableLabel *label;
    QStackedLayout *stacked;
};

#endif // __COMBOLABEL_H
