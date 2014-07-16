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

#ifndef __HISTOGRAPH_H
#define __HISTOGRAPH_H

#include <QDateTime>
#include <QWidget>
#include <QMap>

class Histograph :
    public QWidget
{
    Q_OBJECT

public:
    explicit Histograph(QWidget *parent = 0);
    
    void setData(QMap<time_t, int> history);

private:
    virtual void paintEvent(QPaintEvent*);

private:
    QMap<time_t, int> History;
};

#endif // __HISTOGRAPH_H