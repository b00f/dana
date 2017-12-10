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

#ifndef __CARDQUERY_H
#define __CARDQUERY_H

#include "danaeditor.h"
#include "qxdialog.h"
#include "combolabel.h"
#include "clicktoshowbutton.h"

class Deck;
class Card;
class CardQuery 
{
public:
    CardQuery();

    void startQuery();
    void setDeck(Deck *deck);

    void shuffle();

    bool hasNextCard();
    bool hasPrevCard();

    Card *gotoNextCard();
    Card *gotoPrevCard();
    void setFilterLevel(int _filterLevel);

public:
    QList<Card*> shuffled;

    int currentIndex;
    int filterLevel;

    QDateTime startTime;
    Deck* deck;
};

#endif // __CARDQUERY_H
