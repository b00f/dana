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

#include <QObject>
#include <QMap>

class CardHistory
    : public QObject
{
    Q_OBJECT

public:
    CardHistory(QObject *parent = 0);
    CardHistory(const CardHistory &rhs);
    CardHistory &operator =(const CardHistory &rhs);

    void      fromString(QString historyLine);
    QString   toString();
    QDateTime getLastAccessTime();

    void      addHistoryPoint(int level);
    
    void      getMap(QMap<time_t, int> &historyMap);

protected:
    QMap<time_t, int> historyMap;  
};

#endif // __CARDHISTORY_H