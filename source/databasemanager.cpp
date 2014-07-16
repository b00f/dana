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

#include "databasemanager.h"
#include "qxmessagebox.h"
#include "decklist.h"
#include "mydeck.h"
#include "deck.h"
#include "card.h"
#include "constants.h"

#include <QtSQl\QSqlQuery>
#include <QtSQl\QSqlRecord>
#include <QtDebug>


#define SQL_CREATE_DECK_TABLE      "CREATE TABLE DECK(                           \
                                         ID             INTEGER  PRIMARY KEY,    \
                                         NAME           TEXT                ,    \
                                         DESC           TEXT                ,    \
                                         GUID           TEXT     NOT NULL   ,    \
                                         AUTHOR         TEXT                ,    \
                                         TAGS           TEXT                ,    \
                                         FLAGS          INTEGER  DEFAULT 0  ,    \
                                         INHAND         INTEGER  DEFAULT 0  ,    \
                                         SYNC           INTEGER  DEFAULT 0  ,    \
                                         CREATED        TEXT     NOT NULL   ,    \
                                         UPDATED        TEXT     NOT NULL   ,    \
                                         FORMAT         TEXT               );"

#define SQL_CREATE_CARD_TABLE      "CREATE TABLE CARD(                           \
                                         ID             INTEGER  PRIMARY KEY,    \
                                         DECKID         INTEGER  NOT NULL   ,    \
                                         FRONT          TEXT                ,    \
                                         BACK           TEXT                ,    \
                                         HISTORY        TEXT                ,    \
                                         LEVEL          INTEGER  DEFAULT 0  ,    \
                                         FLAGS          INTEGER  DEFAULT 0  ,    \
                                         SYNC           INTEGER  DEFAULT 0      );"

#define SQL_INSERT_DECK            "INSERT INTO DECK                         \
                                               (NAME, DESC, GUID, AUTHOR, TAGS, FLAGS, CREATED, UPDATED, FORMAT) \
                                         VALUES(:name,:desc,:guid,:author,:tags,:flags,:created,:updated,:format);"


#define SQL_INSERT_CARD            "INSERT INTO CARD                         \
                                               (DECKID, FRONT, BACK, LEVEL, FLAGS, HISTORY)   \
                                         VALUES(:deckid,:front,:back,:level,:flags,:history);"

#define SQL_UPDATE_DECK            "UPDATE DECK                               \
                                         SET     INHAND      = :inhand,       \
                                                 UPDATED     = :updated       \
                                         WHERE   ID          = :deckid;"

#define SQL_UPDATE_DECK_INFO       "UPDATE DECK                               \
                                         SET     NAME        = :name,         \
                                                 DESC        = :desc,         \
                                                 AUTHOR      = :author,       \
                                                 TAGS        = :tags,         \
                                                 FLAGS       = :flags,        \
                                                 FORMAT      = :format,       \
                                                 INHAND      = :inhand,       \
                                                 UPDATED     = :updated       \
                                         WHERE   ID          = :deckid;"


#define SQL_UPDATE_CARD            "UPDATE CARD                              \
                                         SET     FRONT       = :front,       \
                                                 BACK        = :back,        \
                                                 LEVEL       = :level,       \
                                                 FLAGS       = :flags,       \
                                                 HISTORY     = :history      \
                                         WHERE   ID          = :cardid;"

#define SQL_DELETE_DECK            "DELETE FROM DECK WHERE ID=:deckid"
#define SQL_DELETE_DECK_CARDS      "DELETE FROM CARD WHERE DECKID=:deckid"
#define SQL_DELETE_CARD            "DELETE FROM CARD WHERE ID=:cardid"

#define SQL_GET_DECKS              "SELECT *FROM DECK"
#define SQL_GET_CARDS              "SELECT *FROM CARD WHERE DECKID=:deckid"

DatabaseManager::DatabaseManager()
{
    openDB();
}

bool DatabaseManager::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    
    db.setDatabaseName( dBPath() );

    if (!db.open())
        return false;

    if(!db.tables().contains(QLatin1String("DECK")))
    {
        db.exec(SQL_CREATE_DECK_TABLE);
    }

    if(!db.tables().contains(QLatin1String("CARD")))
    {
        db.exec(SQL_CREATE_CARD_TABLE);
    }

    // database opened
    return true;
}

QSqlError DatabaseManager::lastError()
{
    // If opening database has failed user can ask 
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::insertDeck(MyDeck *deck)
{
    QSqlQuery query;
    query.prepare(SQL_INSERT_DECK);

    QUuid guid = QUuid::createUuid();
    QDateTime now = QDateTime::currentDateTime();

    query.bindValue(":name",           deck->getName());
    query.bindValue(":desc",           deck->getDesc());    
    query.bindValue(":author",         deck->getAuthor());
    query.bindValue(":tags",           deck->getTags());
    query.bindValue(":flags",          deck->getFlags());
    query.bindValue(":format",         deck->getFormat().toString());
    query.bindValue(":guid",           guid);
    query.bindValue(":created",        now);
    query.bindValue(":updated",        now);
    
    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    deck->id = query.lastInsertId().toInt();
    deck->guid = guid;
    deck->createdTime = now;
    deck->updatedTime = now;

    return true;
}

bool DatabaseManager::updateDeck(MyDeck *deck)
{
    QDateTime now = QDateTime::currentDateTime();
    QSqlQuery query;
    query.prepare(SQL_UPDATE_DECK_INFO);
    
    query.bindValue(":deckid",         deck->getId());
    query.bindValue(":name",           deck->getName());
    query.bindValue(":desc",           deck->getDesc());
    query.bindValue(":author",         deck->getAuthor());
    query.bindValue(":tags",           deck->getTags());
    query.bindValue(":flags",          deck->getFlags());
    query.bindValue(":format",         deck->getFormat().toString());
    query.bindValue(":inhand",         deck->getInHandCardsNo());
    query.bindValue(":updated",        now);

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    deck->updatedTime = now;

    return true;
}

bool DatabaseManager::deleteDeck(MyDeck *deck)
{
    QSqlQuery query;
    query.prepare(SQL_DELETE_DECK_CARDS);

    query.bindValue(":deckid", deck->getId());

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    query.prepare(SQL_DELETE_DECK);

    query.bindValue(":deckid", deck->getId());

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::loadDeckList(DeckList *deckList)
{
    deckList->clear();

    QSqlQuery query;
    query.prepare(SQL_GET_DECKS);

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    int idFieldNo       = query.record().indexOf("ID");
    int nameFieldNo     = query.record().indexOf("NAME");
    int descFieldNo     = query.record().indexOf("DESC");
    int guidFieldNo     = query.record().indexOf("GUID");
    int authorFieldNo   = query.record().indexOf("AUTHOR");
    int tagsFieldNo     = query.record().indexOf("TAGS");
    int flagsFieldNo    = query.record().indexOf("FLAGS");
    int inhandFieldNo   = query.record().indexOf("INHAND");
    int createdFieldNo  = query.record().indexOf("CREATED");
    int updatedFieldNo  = query.record().indexOf("UPDATED");
    int formatFieldNo   = query.record().indexOf("FORMAT");  

    while (query.next()) {
        MyDeck *deck = new MyDeck;

        deck->setName    (query.value(nameFieldNo ).toString() );
        deck->setDesc    (query.value(descFieldNo ).toString() );        
        deck->setAuthor  (query.value(authorFieldNo).toString());
        deck->setTags    (query.value(tagsFieldNo ).toString() );
        deck->setFlags   (query.value(flagsFieldNo).toUInt()   );        
        
        deck->id             = query.value(idFieldNo   ).toInt()       ;
        deck->guid           = query.value(guidFieldNo ).toUuid()      ;
        deck->inhand         = query.value(inhandFieldNo).toInt()      ;
        deck->createdTime    = query.value(createdFieldNo).toDateTime();
        deck->updatedTime    = query.value(updatedFieldNo).toDateTime();
        deck->format.fromString(query.value(formatFieldNo).toString());

        deck->loadPixmap( deck->getPixmapPath() );

        deckList->addDeck(deck);
    }

    return true;
}


bool DatabaseManager::insertCard(Card *card, int deckId)
{
    QSqlQuery query;
    query.prepare(SQL_INSERT_CARD);

    /// initialize card history here
    card->getHistory().addHistoryPoint( card->getLevel() );

    query.bindValue(":deckid",         deckId);
    query.bindValue(":front",          card->getFront());
    query.bindValue(":back",           card->getBack());
    query.bindValue(":level",          card->getLevel());
    query.bindValue(":flags",          card->getFlags());    
    query.bindValue(":history",        card->getHistory().toString());

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    card->setId(query.lastInsertId().toInt());

    return true;
}

bool DatabaseManager::updateCard(Card *card)
{
    QSqlQuery query;
    query.prepare(SQL_UPDATE_CARD);

    query.bindValue(":cardid",         card->getId());
    query.bindValue(":front",          card->getFront());
    query.bindValue(":back",           card->getBack());
    query.bindValue(":level",          card->getLevel());
    query.bindValue(":flags",          card->getFlags());
    query.bindValue(":history",        card->getHistory().toString());   

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteCard(Card *card)
{
    QSqlQuery query;
    query.prepare(SQL_DELETE_CARD);

    query.bindValue(":cardid", card->getId());

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::saveDeck(MyDeck *deck)
{
    int count = deck->getTotalCardsNo();
    bool hasChange = false;
    int inHandCardNo = 0;

    for(int index = 0; index < count; index++) {
        Card *card = deck->getCardAt(index);

        if(card->isInHand())
            inHandCardNo ++;

        if(card->isModified()) {
            hasChange = true;
            updateCard(card);

            card->resetModification();
        }
    }

    deck->inhand = inHandCardNo;
    if(hasChange) {
        QDateTime now = QDateTime::currentDateTime();
        QSqlQuery query;
        query.prepare(SQL_UPDATE_DECK);

        query.bindValue(":inhand",  inHandCardNo);
        query.bindValue(":deckid",  deck->getId());
        query.bindValue(":updated", now);
        
        query.exec();

        deck->updatedTime = now;
    }

    return true;
}

void DatabaseManager::loadDeck(MyDeck *deck)
{
    deck->clear();

    QSqlQuery query;
    query.prepare(SQL_GET_CARDS);

    query.bindValue(":deckid", deck->getId());

    if(!query.exec()) {
        /// report error
        qCritical() << query.lastError();
        return;
    }

    int idFieldNo       = query.record().indexOf("ID");
    int frontFieldNo    = query.record().indexOf("FRONT");
    int backFieldNo     = query.record().indexOf("BACK");
    int levelFieldNo    = query.record().indexOf("LEVEL");
    int flagsFieldNo    = query.record().indexOf("FLAGS"); 
    int historyFieldNo  = query.record().indexOf("HISTORY");
 
    while (query.next()) {
        Card *card = new Card;

        card->setId          (query.value(idFieldNo    ).toInt()     );
        card->updateFront    (query.value(frontFieldNo ).toString()  );
        card->updateBack     (query.value(backFieldNo  ).toString()  );
        card->updateLevel    (query.value(levelFieldNo ).toInt()     );
        card->setFlags       (query.value(flagsFieldNo ).toUInt()    );
        card->getHistory().fromString(query.value(historyFieldNo).toString()  );

        card->resetModification();

        deck->cards.append(card);
    }
}