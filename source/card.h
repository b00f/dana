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

#ifndef __CARD_H
#define __CARD_H

#include "modifier.h"
#include "cardhistory.h"

#include <QDateTime>
#include <QString>
#include <QPixmap>
#include <QColor>
#include <QMap>


class Card
    : public QObject
    , public Modifier
{
    Q_OBJECT

public:
    enum Difficulty {
        Easy=0,
        Normal,
        Hard
    };

    Card(QObject *parent = 0);
    Card(const Card &right, QObject *parent = 0);

    bool  operator== (const Card &right) const;
    Card &operator=  (const Card &right);

    bool         compare(const Card &right) const;

    void         setId(int id);
    void         updateFront(QString front);
    void         updateBack(QString back);
    void         updateLevel(int level);
    void         setLevel(int _level);
    void         setFlags(uint flags);

    int          getId() const;
    QString      getFront() const;
    QString      getBack() const;
    int		     getLevel() const;
    uint         getFlags() const;
    QString      getFrontPlain() const;
    QString      getBackPlain() const;
    Difficulty   getDifficulty() const;
    bool         isStarred() const;
    bool         isInHand() const;
    bool         isRetiree() const;
    QDateTime    getCreationTime() const;

    CardHistory *getHistory();

    void         turnStarFlag();
    void         increaseStudy();
    void         increaseLevel();
    void         decreaseLevel();


    static QColor    getLevelColor(int level);
    static QString   getLevelString(int level);
    static QString   getLevelPercentage(int level);
    static QString   getDifficultyString(Difficulty difficulty);
    static QPixmap   getDifficultyPixmap(Difficulty difficulty);
    static QString   getStarredString(bool starred);
    static QPixmap   getStarredPixmap(bool starred);

protected:

protected:
    int         id;
    QString     frontPlain;
    QString     front;
    QString     back;
    int         level;
    uint        flags;
    CardHistory history;

};

#endif // __CARD_H
