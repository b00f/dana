//
// Dana - Dana, Symbol of Wisdom
// Copyright (C) 2014 Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
//
// This file is part of Dana.
//
// Dana is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dana is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dana.  If not, see <http://www.gnu.org/licenses/>.
//

#include "cardhistory.h"

#include <QDateTime>
#include <QStringList>

CardHistory::CardHistory(QObject *parent)
    : QObject(parent)
{
}

CardHistory::CardHistory(const CardHistory &rhs)
{
    *this = rhs;
}

CardHistory &CardHistory::operator =(const CardHistory &rhs)
{
    historyMap = rhs.historyMap;

    return *this;
}

void CardHistory::addHistoryPoint(int level)
{
    time_t tm = QDateTime::currentDateTime().toTime_t();

    historyMap.insert(tm, level);
}

void CardHistory::fromString(QString historyLine)
{
    historyMap.clear();

    int index = 0;
    int level = 0;
    time_t time = 0;
    QString token;
    QStringList sl = historyLine.split(';');

    for (QStringList::Iterator it=sl.begin(); 
        it!=sl.end(); ++it) {
            token = *it;
            index = token.indexOf(',');

            if(index != -1)
            {
                level = token.midRef(index+1).toInt();
                time = token.leftRef(index).toLongLong();

                historyMap.insert(time, level);
            }
    }
}

QString CardHistory::toString()
{
    QString historyLine;
    for (QMap<time_t, int>::Iterator it=historyMap.begin(); 
        it!=historyMap.end(); ++it) {
             historyLine.append(QString("%1,%2;").arg(it.key()).arg(it.value()));
    }

    return historyLine;
}

void CardHistory::getMap(QMap<time_t, int> &_historyMap)
{
    _historyMap = historyMap;
}

QDateTime CardHistory::getLastAccessTime()
{
    return QDateTime::fromTime_t(historyMap.end().key());
}