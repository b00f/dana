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

#ifndef __DECKLIST_H
#define __DECKLIST_H

#include <QVariant>
#include <QObject>
#include <QList>

class Deck;
class DeckList 
    : public QObject
{
    Q_OBJECT

public:
    DeckList(QObject *parent = 0);
    virtual ~DeckList();

    virtual void  clear();
    virtual void  addDeck(Deck *deck);
    virtual void  removeOneDeck(Deck *deck);
    virtual int   getCount() const;
    virtual Deck *getDeckAt(int index) const;
    virtual Deck *findDeckById(const QUuid &guid) const;

    void Sort();

protected:
    QList<Deck*> decks;    
};

#endif // __DECKLIST_H