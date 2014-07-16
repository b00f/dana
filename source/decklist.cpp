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

#include "decklist.h"
#include "deck.h"

#include <QListIterator>

bool deckCompare(const Deck *a, const Deck *b)
{
    bool lessThan = a->getName() > b->getName();

    return lessThan;
}


DeckList::DeckList(QObject *parent)
    : QObject(parent)
{
    
}

DeckList::~DeckList()
{
    clear();
}

void DeckList::clear()
{
    QListIterator<Deck *> i(decks);
    while (i.hasNext())
        delete i.next();

    decks.clear();
}

void DeckList::addDeck(Deck *deck)
{
    decks.append(deck);
}

void DeckList::removeOneDeck(Deck *deck)
{
    deck->removeDeck();

    decks.removeOne(deck);
}

void DeckList::Sort()
{
    /// sort decks
   qSort(decks.begin(), decks.end(), deckCompare);
}

int DeckList::getCount() const
{
    return decks.count();
}

Deck *DeckList::getDeckAt(int index) const
{
    if( index < 0 || 
        index >= decks.count())
        return 0;

    return decks.at(index);
}

Deck *DeckList::findDeckById(const QUuid &guid) const
{
    Deck* deck = 0;
    QListIterator<Deck *> i(decks);
    while (i.hasNext()) {
        deck = i.next();
        if(deck->getGuid()==guid)
            return deck;
    }

    return 0;
}