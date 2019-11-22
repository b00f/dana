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

#ifndef __ICONBUTTON_H
#define __ICONBUTTON_H

#include <QObject>
#include <QPushButton>

class QToolButton;

class IconButton : public QPushButton
{
    Q_OBJECT

public:
    IconButton(QWidget *parent = 0);

    void setPixmap(QPixmap pixmap);
    QPixmap getPixmap();

    void setDefaultPixmap(QPixmap defaultPixmap);
    void setDefaultSize(int size);

    void setReadOnly(bool ro);

protected:
	void paintEvent (QPaintEvent *);

private slots:
	void onResetIcon();
    void onSetIcon();

private:
    QToolButton *clearButton;
    QPixmap defaultPixmap;
    QSize size;
    QPixmap pixmap;
};

#endif // __ICONBUTTON_H
