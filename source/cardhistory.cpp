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

CardHistory::CardHistory()
{
}

CardHistory::CardHistory(const CardHistory &rhs)
{
    *this = rhs;
}

CardHistory::~CardHistory()
{
    for (auto it=history.constBegin();
        it!=history.constEnd(); ++it) {
        delete (*it);
    }
    history.clear();
}

CardHistory &CardHistory::operator =(const CardHistory &rhs)
{
    history = rhs.history;

    return *this;
}

void CardHistory::addPoint(int level)
{
    Point* point = new Point();

    point->time = QDateTime::currentDateTime();
    point->level = level;

    history.push_back(point);
}

void CardHistory::fromString(QString historyLine)
{
    history.clear();

    int index = 0;
    int level = 0;
    time_t time = 0;
    QString token;
    QStringList sl = historyLine.split(';');

    for (QStringList::Iterator it=sl.begin();
         it!=sl.end(); ++it) {
        token = *it;
        index = token.indexOf(',');

        if(index != -1) {
            level = token.midRef(index+1).toInt();
            time = token.leftRef(index).toLongLong();

            Point* point = new Point();

            point->time = QDateTime::fromTime_t(time);
            point->level = level;

            history.push_back(point);
        }

    }
}

QString CardHistory::toString() const
{
    QString historyLine;
    for (auto it=history.constBegin();
        it!=history.constEnd(); ++it) {
             historyLine.append(QString("%1,%2;")
                                .arg((*it)->time.toTime_t())
                                .arg((*it)->level));
    }

    return historyLine;
}

Point* CardHistory::getLastPoint(bool same_level) const
{
    Point* point = 0;

    if(same_level) {
        int level = history[history.size()-1]->level;
        int index = history.size()-2;

        for(; index >= 0; --index) {

            if(level != history[index]->level) {
                break;
            }
        }

        point = history[index+1];

    } else {
        point = history[history.size()-1];
    }

    return point;
}

int CardHistory::difficulty() const
{
    int level = 0;
    int success = 0;
    for (auto it=history.constBegin();
        it!=history.constEnd(); ++it) {
        if((*it)->level >= level)
            success++;
        else
            success--;
    }

    if(success>5) {
        return 1;
    } else if(success<-3) {
        return -1;
    } else {
        return 0;
    }
}
