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

#ifndef __DATABASEMANAGER_H
#define __DATABASEMANAGER_H

#include "singleton.h"

#include <QtSQl\QSqlDatabase>
#include <QtSQl\QSqlError>
#include <QVariant>

class DeckList;
class MyDeck;
class Card;
class DatabaseManager
    : public CSingleton<DatabaseManager>
{
public:
    DatabaseManager();
	
	bool openDB();
    QSqlError lastError();
    
    bool loadDeckList(DeckList *deckList);

    bool saveDeck(MyDeck *deck);
    void loadDeck(MyDeck *deck);

    bool insertDeck(MyDeck *deck);
    bool deleteDeck(MyDeck *deck);

    bool insertCard(Card *card, int deckId);    
    bool deleteCard(Card *card);

    bool updateDeck(MyDeck *deck);
    bool updateCard(Card *card);    

private:
    QSqlDatabase db;
};

#endif // __DATABASEMANAGER_H
