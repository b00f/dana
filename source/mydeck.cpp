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

#include "mydeck.h"
#include "databasemanager.h"
#include "constants.h"
#include "card.h"


MyDeck::MyDeck(QObject *parent)
    : Deck(Type_MyDeck, parent)
{
}

MyDeck::~MyDeck()
{
    saveDeck();
    closeDeck();
}

void MyDeck::saveDeck()
{
    if(id==-1) {
        DatabaseManager::GetInstance()->insertDeck(this);
        utils::createDirectory( getDeckPath() );
    } else {
        DatabaseManager::GetInstance()->updateDeck(this);
    }

    savePixmap();
}

void MyDeck::removeDeck()
{
    if(DatabaseManager::GetInstance()->deleteDeck(this)) {
        utils::removeDirectory( getDeckPath() );
    }
}

void MyDeck::savePixmap()
{
    QString iconPath = getPixmapPath();
    
    pixmap.save(iconPath);
}

bool MyDeck::openDeck(QVariant param)
{
    Q_UNUSED(param);

    if(opened)
        return true;

    DatabaseManager::GetInstance()->loadDeck(this);

    opened = true;

    return true;
}

void MyDeck::closeDeck(QVariant param)
{
    Q_UNUSED(param);

    if(!opened)
        return;

    DatabaseManager::GetInstance()->saveDeck(this);

    opened = false;
}

void MyDeck::addCard(Card *card)
{
    if(DatabaseManager::GetInstance()->insertCard(card, id)) {
        Deck::addCard(card);
    }
}

void MyDeck::removeOneCard(Card *card)
{
    if(DatabaseManager::GetInstance()->deleteCard(card)) {
        Deck::removeOneCard(card);
    }
}

QString MyDeck::getDeckPath() const
{ 
    QString deckPath = 
        utils::combinePaths(danaPath(), QString("decks/%1").arg(id));

    utils::createDirectory(deckPath);

    return deckPath;
}

QString MyDeck::getPixmapPath() const
{
    QString iconPath = 
        utils::combinePaths(getDeckPath(), QString("icon.png"));
    
    return iconPath;
}
