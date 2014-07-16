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

#include "card.h"
#include "constants.h"

#include <QString>

#define FLAG_STAR       0x00000001
#define FLAG_EASY       0x00000002
#define FLAG_HARD       0x00000004


Card::Card(QObject *parent)
    : QObject(parent)
{
    level=0;
    flags=0;
    id=-1;
}

Card::Card(const Card &right)
{
    *this=right;
}

bool Card::operator== (const Card &right) const
{
    return compare(right);
}

bool Card::compare(const Card &right) const
{
    if(frontPlain.compare(right.frontPlain)==0)
        return true;

    return false;
}

Card &Card::operator=  (const Card &right)
{
    id=right.id;
    frontPlain=right.frontPlain;
    front=right.front;
    back=right.back;
    level=right.level;
    history=right.history;
    flags=right.flags;

    return *this;
}

void Card::updateFront(QString _front)
{
    setModified(true);

    front = _front.trimmed();
    frontPlain = utils::HTML2Plain(_front);
}

void Card::updateBack(QString _back)
{
    setModified(true);

    back = _back.trimmed();
}

void Card::setId(int _id)
{
    id = _id;
}

void Card::setFlags(uint _flags)
{
    flags = _flags;
}

int Card::getId() const
{
    return id;
}

QString Card::getFront() const
{
    return front;
}

QString Card::getFrontPlain() const
{
    return frontPlain;
}

QString Card::getBack() const
{
    return back;
}

QString Card::getBackPlain() const
{
    return utils::HTML2Plain(back);
}

int Card::getLevel() const
{
    return level;
}

uint Card::getFlags() const
{
    return flags;
}

QString Card::getLevelString(int level)
{
    return LevelsName[level];
}

QString Card::getLevelPercentage(int level)
{
    return QString("%%1").arg( (level*(100/LevelCount)) );;
}

QColor Card::getLevelColor(int level)
{
    return LevelsColor[level];
}

Card::Difficulty Card::getDifficulty() const
{
    if(IS_FLAG_SET(flags, FLAG_EASY))
        return Easy;

    if(IS_FLAG_SET(flags, FLAG_HARD))
        return Hard;

    return Normal;
}

QString Card::getDifficultyString(Difficulty difficulty)
{
    const static QString strings[3] = { 
        STR_CARD_DIFFICULTY_EASY,        
        STR_CARD_DIFFICULTY_NORMAL,
        STR_CARD_DIFFICULTY_HARD};

    return strings[ difficulty%3 ];
}

QPixmap Card::getDifficultyPixmap(Difficulty difficulty)
{
    switch(difficulty){
    case Hard:
        return QPixmap(PIXMAP_DIFFICULTY_HARD);

    case Normal:
        return QPixmap(PIXMAP_DIFFICULTY_NORMAL);

    case Easy:
        return QPixmap(PIXMAP_DIFFICULTY_EASY);
    }

    return QPixmap();
}

QPixmap Card::getStarredPixmap(bool starred)
{
    if(starred)
        return QPixmap(PIXMAP_STARRED);

    return QPixmap(PIXMAP_UNSTARRED);
}

QString Card::getStarredString(bool starred)
{
    if(starred)
        return STR_STARRED;

    return STR_NOPE;
}

void Card::increaseLevel()
{
    updateLevel(level+1);
}

void Card::decreaseLevel()
{
    updateLevel(level-1);
}

bool Card::isInHand() const
{
    return (level<LevelCount);
}

bool Card::isStarred() const
{
    return IS_FLAG_SET(flags, FLAG_STAR);
}

void Card::turnStarFlag()
{
    setModified(true);

    TURN_FLAG(flags, FLAG_STAR);
}

void Card::updateLevel(int _level)
{
    setModified(true);
    
    if(_level<Level_1)
        level=Level_1;
    else if(_level>LevelCount)
        level=Level_Retired;
    else
        level=_level;

    history.addHistoryPoint(level);

    /// 
    int level = -1;
    int passed = 0;
    QMap<time_t, int> historyMap;
    history.getMap(historyMap);

    QMapIterator<time_t, int> itr(historyMap);

    while(itr.hasNext())
    {
        itr.next();

        if(level < itr.value())
            passed++;
        else
            passed--;

        level = itr.value();
    }

    if(passed>2) {
        SET_FLAG(flags, FLAG_EASY);
    } else if(passed<-1) {
        SET_FLAG(flags, FLAG_HARD);
    } else {
        UNSET_FLAG(flags, FLAG_EASY);
        UNSET_FLAG(flags, FLAG_HARD);
    }
}

CardHistory &Card::getHistory()
{
    return history;
}