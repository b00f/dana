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
    return a->getHistory()->getLastPoint()->time <
           b->getHistory()->getLastPoint()->time;
}


CardQuery::CardQuery()
    : currentIndex(-1)
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
    int count = deck->getTotalCardsNo();
    QVector<int> index(count);

    for (int i=0; i<count; i++) {
        index[i] = i;  // fill the array in order
    }

    //--- Shuffle elements by randomly exchanging each with one other.
    srand (time(NULL));
    for (int i=0; i<count; i++) {
        int r = rand() % count;  // generate a random position
        int temp = index[i]; index[i] = index[r]; index[r] = temp;
    }

    /// remove Retiree cards

    Card *card=0;
    for(int i = 0; i < count; i++) {
        card=deck->getCardAt(index[i]);
        if(Level_Retiree != card->getLevel()) {
            shuffled.append(card);
        }
    }

    currentIndex=-1;
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
