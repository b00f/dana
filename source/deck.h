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

#ifndef __DECK_H
#define __DECK_H

#include "deckformat.h"

#include <QDomElement>
#include <QDateTime>
#include <QList>
#include <QIcon>
#include <QUuid>


class Card;
class Deck 
    : public QObject
{
    Q_OBJECT

public:
    enum DeckType {
        Type_MyDeck     = 0,
        Type_iDeck         ,
        Type_TempDeck      ,
    };

    enum MergeOption {
        AcceptSource = 0, 
        AcceptTarget, 
        AutoMerge
    };
    
    Deck(int type, QObject *parent = 0);
    virtual ~Deck();

    virtual int         getType() const;
    virtual int         getId() const;
    virtual QString     getName() const;
    virtual QString     getDesc() const;
    virtual QString     getTags() const;
    virtual uint        getFlags() const;
    virtual QString     getAuthor() const;
    virtual QPixmap     getPixmap() const;
    virtual QUuid       getGuid() const;
    virtual QDateTime   getCreatedTime() const;
    virtual QDateTime   getUpdatedTime() const;

    virtual DeckFormat &getFormat();
        
    virtual void setName(QString name);
    virtual void setDesc(QString desc);
    virtual void setPixmap(QPixmap pixmap);
    virtual void setAuthor(QString author);
    virtual void setTags(QString tags);
    virtual void setFlags(uint flags);
    virtual void setFormat(DeckFormat format);
    
    virtual void  saveDeck() = 0;
    virtual void  removeDeck() = 0;

    virtual bool  openDeck(QVariant param = QVariant()) = 0;
    virtual void  closeDeck(QVariant param = QVariant()) = 0;

    virtual void  clear();
    virtual void  addCard(Card *card);
    virtual void  removeOneCard(Card *card);
    virtual Card *getCardAt(int index) const;    
    virtual int   getTotalCardsNo() const;
    virtual int   getInHandCardsNo() const;
    virtual int   getCardsNo(int level = /*Level_ALL*/-1) const;

    bool importDeck(QVariant param);
    bool exportDeck(QVariant param);

    void Merge(Deck *dst, int option = AcceptTarget, int *stats = 0);

protected:
    virtual QString    getDeckPath() const = 0;
    virtual void       loadPixmap(QString path);

protected:
    bool importDana(QString fileName);
    bool importMnemosyne(QString fileName);
    bool importFromTxt(QString fileName);
    bool importFromXml(QString fileName);

    bool exportToXml(QString fileName);
    bool exportToTxt(QString fileName);
    bool exportToDana(QString fileName);
    
protected:
    /// properties:
    int          type  ;
    int          id    ;
    QString      name  ;
    QString      desc  ;
    QString      author;
    QString      tags  ;
    QUuid        guid  ;
    uint         flags ;
    int          inhand;
    QPixmap      pixmap;
    QDateTime    createdTime;    
    QDateTime    updatedTime; 
    DeckFormat   format;
    
    QList<Card *> cards;

    bool       opened;
};


#endif // __DECK_H