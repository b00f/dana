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

#ifndef __SEARCHEDIT_H
#define __SEARCHEDIT_H

#include <QLineEdit>
#include <QStaticText>
#include <QToolButton>


class SearchEdit 
    : public QLineEdit
{
    Q_OBJECT

public:
    SearchEdit(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
	void focusOutEvent(QFocusEvent *);
	void focusInEvent(QFocusEvent *);
	void paintEvent(QPaintEvent *);

private slots:
    void updateCloseButton(const QString &text);

private:
    QToolButton *clearButton;
    QToolButton *searchButton;
	bool drawSearchLabel;
};

#endif // __SEARCHEDIT_H