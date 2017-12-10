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

#ifndef __CARDHISTORY_H
#define __CARDHISTORY_H

#include <QDateTime>
#include <QList>

class Point
{
public:
    QDateTime time;
    int level;
};

class CardHistory
{
public:
    CardHistory();
    CardHistory(const CardHistory &rhs);
    CardHistory &operator =(const CardHistory &rhs);
    ~CardHistory();

    void      fromString(QString historyLine);
    QString   toString() const;
    Point*    getLastPoint(bool sameLevel = false) const;

    void      addPoint(int level);

    const QList<Point*> &getPoints() const;

protected:
    QList<Point*> points;
};

#endif // __CARDHISTORY_H
