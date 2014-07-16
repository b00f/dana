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

#include "cardquery.h"
#include "constants.h"
#include "preferences.h"
#include "deck.h"
#include "card.h"

bool timeCompare(/*const */Card *a, /*const */Card *b)
{
    bool lessThan = a->getHistory().getLastAccessTime() < b->getHistory().getLastAccessTime();

    return lessThan;
}


CardQuery::CardQuery(QObject *parent)
    : QObject(parent)
    , currentIndex(-1)
    , filterLevel(Level_ALL)
    , deck(0)
{
}

void CardQuery::startQuery()
{
    startTime = QDateTime::currentDateTime();
}

void CardQuery::setFilterLevel(int _filterLevel)
{
    filterLevel = _filterLevel;
}

void CardQuery::setDeck(Deck *_deck)
{
    deck = _deck;
}

void CardQuery::shuffle()
{
    shuffled.clear();

    /// remove retired cards
    int count = deck->getTotalCardsNo();
    Card *card=0;
    for(int index = 0; index < count; index++) {
        card=deck->getCardAt(index);
        if(Level_Retired != card->getLevel()) {
            shuffled.append(card);
        }
    }

    currentIndex=-1;

    if( Preferences::GetInstance()->getShufflingMethod() == Preferences::ByDate) {
        /// sort cards by time
        qSort(shuffled.begin(), shuffled.end(), timeCompare);
    } else {
        QTime now = QTime::currentTime();
        qsrand(now.msec());
        int n = shuffled.size();
        for (int i = n-1; i > 0; --i) {
            shuffled.swap(i, qrand()%(i+1));
        }
    }
}

Card *CardQuery::gotoNextCard()
{
    Card *nextCard = 0;
    int level = 0;
    int count = shuffled.count();

    while(currentIndex<count-1) {
        currentIndex++;
        level = shuffled[currentIndex]->getLevel();

        if(filterLevel == Level_ALL ||
           filterLevel == level) {

            nextCard = shuffled[currentIndex];
            break;
        }
    }

    return nextCard;
}

Card *CardQuery::gotoPrevCard()
{
    Card *prevCard = 0;
    int level = 0;
    while(currentIndex>0) {
        currentIndex--;
        level = shuffled[currentIndex]->getLevel();

        if(filterLevel == Level_ALL ||
            filterLevel == level) {

            prevCard = shuffled[currentIndex];
            break;
        }
    }

    return prevCard;
}

bool CardQuery::hasNextCard()
{
    int temp = currentIndex;
    bool hasNext = gotoNextCard();

    currentIndex = temp;

    return hasNext;
}

bool CardQuery::hasPrevCard()
{
    int temp = currentIndex;
    bool hasPrev = gotoPrevCard();

    currentIndex = temp;

    return hasPrev;
}