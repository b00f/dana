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

#ifndef __MYDECK_H
#define __MYDECK_H

#include "deck.h"


class MyDeck 
    : public Deck
{
    friend class DatabaseManager;

    Q_OBJECT

public:
    MyDeck(QObject *parent = 0);
    ~MyDeck();

    void saveDeck();
    void removeDeck();

    bool openDeck(QVariant param = QVariant());
    void closeDeck(QVariant param = QVariant());

    void addCard(Card *card);
    void removeOneCard(Card *card);
	
    QString getDeckPath() const;
    QString getPixmapPath() const;

    void savePixmap();
};

#endif // __MYDECK_H