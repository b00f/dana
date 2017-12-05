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

#include "deck.h"
#include "card.h"
#include "zlibwrappr.h"
#include "constants.h"

#include <QXmlStreamWriter>
#include <QTemporaryFile>
#include <QDomDocument>
#include <QDomNodeList>
#include <QTextFormat>
#include <QFileInfo>
#include <QVariant>
#include <QDebug>

Deck::Deck(int type, QObject *parent)
    : QObject(parent)
    , type(type)
{
    inhand = 0;
    flags = 0;
    id = -1;
    opened = false;
    /// createdTime = QDateTime::currentDateTime();
}

Deck::~Deck()
{
    clear();
}

void Deck::clear()
{
    QListIterator<Card *> i(cards);
    while (i.hasNext())
        delete i.next();

    cards.clear();
}

int Deck::getType() const
{
    return type;
}

int Deck::getId() const
{
    return id;
}

QString Deck::getName() const
{
    return name;
}

QString Deck::getDesc() const
{
    return desc;
}

QString Deck::getAuthor() const
{
    return author;
}

QString Deck::getTags() const
{
    return tags;
}

uint Deck::getFlags() const
{
    return flags;
}

QDateTime Deck::getCreatedTime() const
{
    return createdTime;
}

QDateTime Deck::getUpdatedTime() const
{
    return updatedTime;
}

QPixmap Deck::getPixmap() const
{
    if(pixmap.isNull())
        return PIXMAP_DECK_64;

    return pixmap;
}

QUuid Deck::getGuid() const
{
    return guid;
}

DeckFormat &Deck::getFormat()
{
    return format;
}

void Deck::setFormat(DeckFormat _format)
{
    format = _format;
}

void Deck::setName(QString _name)
{
    name = _name;
}

void Deck::setDesc(QString _desc)
{
    desc = _desc;
}

void Deck::setPixmap(QPixmap _pixmap)
{
    pixmap = _pixmap;
}

void Deck::setAuthor(QString _author)
{
    author = _author;
}

void Deck::setTags(QString _tags)
{
    tags = _tags;
}

void Deck::setFlags(uint _flags)
{
    flags = _flags;
}

void Deck::Merge(Deck *dst, int option, int *stats)
{
    /// first of all, open the deck!
    if(!openDeck())
        return;

    int rightCount = dst->getCardsNo();
    int leftCount = this->getCardsNo();
    Card *rightCard=0;
    Card *leftCard=0;
    bool hasMerged = false;

    if(stats)
        *stats = 0;

    QList<Card*> cards;

    for(int i=0; i < rightCount; i++) {
        rightCard = dst->getCardAt(i);

        hasMerged = false;

        for(int j=0; j < leftCount; j++) {
            leftCard = this->getCardAt(j);

            if(leftCard->compare(*rightCard)) {
                
                hasMerged = true;
                switch(option) {
                case AcceptSource:
                    break;

                case AcceptTarget:
                    leftCard->updateBack(rightCard->getBack());
                    break;

                case AutoMerge: 
                    hasMerged = false;
                    break;
                }

                break;
            }
        }

        if(!hasMerged) {
            if(stats)
                (*stats)++;

            Card *card = new Card(*rightCard);

            cards.append(card);
        }
    }

    /// flush list to deck
    for(int index = 0; index < cards.size(); index++) {
        addCard(cards[index]);
    }

    /// update deck info
    if(option!=AcceptSource) {
        name = dst->getName();
        desc = dst->getDesc();
        author = dst->getAuthor();
        tags = dst->getTags();
        pixmap = dst->getPixmap();
        format = dst->getFormat();
        flags = dst->getFlags();
    }

    utils::copyDirectory(getDeckPath(), dst->getDeckPath());

    saveDeck();
}

void Deck::addCard(Card *card)
{
    if(card->isInHand())
        inhand++;

    cards.append(card);
}

void Deck::removeOneCard(Card *card)
{
    if(card->isInHand())
        inhand--;

    cards.removeOne(card);
}

Card *Deck::getCardAt(int index) const
{
    if( index < 0 || 
        index >= cards.count())
        return 0;

    return cards[index];
}

int Deck::getTotalCardsNo() const
{
    return cards.count();
}

int Deck::getInHandCardsNo() const
{
    return inhand;
}

QString Deck::getCardsNo_str(int level) const
{
    return cardNumberToString(getCardsNo(level));
}

int Deck::getCardsNo(int level) const
{
    int count = 0;
    QListIterator<Card*> iter(cards);

    Card *card=0;
    while (iter.hasNext()) {
        card=iter.next();

        if(level == Level_Retired)
        {
            if(!card->isInHand())
                count ++;

        } else if(level == Level_Starred)
        {
            if(card->isStarred())
                count ++;

        } else if(level == Level_ALL ||
                  level == card->getLevel())
            count ++;
    }

    return count;
}

bool Deck::exportDeck(QVariant param)
{
    /// first of all, open the deck!
    if(!openDeck())
        return false;

    QString fileName = param.toString();
    QFileInfo fi(fileName);
    QString suffix = fi.suffix().toLower();
    QString baseName = fi.baseName().toLower();

    if(suffix == dana_suffix) {
        return exportToDana(fileName);
    } else if(suffix == xml_suffix) {
        return exportToXml(fileName);
    } else if(suffix == txt_suffix) {
        return exportToTxt(fileName);
    } 

    /// Unknown file name!
    return false;
}


bool Deck::importDeck(QVariant param)
{
    QString fileName = param.toString();
    QFileInfo fi(fileName);
    QString suffix = fi.suffix().toLower();
    QString baseName = fi.baseName().toLower();

    if(suffix == dana_suffix) {
        return importDana(fileName);
    } else if(suffix == xml_suffix) {
        return importFromXml(fileName);
    } else if(suffix == txt_suffix) {
        return importFromTxt(fileName);
    } else if(suffix == cards_suffix) {
        return importMnemosyne(fileName);
    }

    /// Unknown file name!
    return false;
}

bool Deck::importMnemosyne(QString fileName)
{
    QFileInfo fi(fileName);
    QString baseName = fi.baseName().toLower();

    QString tempFolder = utils::combinePaths(tempPath(), baseName);
    QString metadataPath = utils::combinePaths(tempFolder, "METADATA"); 
    QString cardsPath = utils::combinePaths(tempFolder, "cards.xml"); 

    utils::createDirectory(tempFolder);

    if(!zlibWrappr::unzipFolder(fileName, tempFolder)) {
        return false;
    }

    /// import metadata
    ///
    QTextStream s;
    QFile metadataFile(metadataPath);

    metadataFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!metadataFile.isOpen())
        return false;

    s.setDevice(&metadataFile);
    s.setCodec("UTF-8");

    QStringList sl;
    QString l = s.readLine();
    while (!s.atEnd()) {
        sl = l.split(":");

        if(sl.size()>1) {
            if(sl[0]=="tags")
                setTags(sl[1]);
            else if(sl[0]=="notes")
                setDesc(sl[1]);
            else if(sl[0]=="author_name")
                setAuthor(sl[1]);
            else if(sl[0]=="card_set_name")
                setName(sl[1]);
        }

        l = s.readLine();
    }

    /// read cards
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;
    QString front, back, level;
    QFile cardsFile(cardsPath);

    cardsFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!cardsFile.isOpen())
        return false;

    if (!domDocument.setContent(&cardsFile, true, &errorStr, &errorLine,
        &errorColumn)) {
            qDebug() << QString("Parse error at line %1, column %2:\n%3")
                .arg(errorLine)
                .arg(errorColumn)
                .arg(errorStr);
            return false;
    }

    QDomElement root = domDocument.documentElement();
    QString rootName = root.tagName().toLower();

    if (rootName == "opensm2sync") {
        QDomNodeList nodes = root.elementsByTagName("log");
        QDomNode node;
        QDomElement elnode;
        
        int count = nodes.count();

        for(int no = 0; no < count; no++) {
            node = nodes.at(no);

            if(node.attributes().namedItem("type").nodeValue()=="16") {
                elnode = node.firstChildElement("f");
                front = elnode.text();

                elnode = node.firstChildElement("b");
                back = elnode.text();

                if(!front.isEmpty()) {
                    Card *card = new Card();

                    card->updateFront(front);
                    card->updateBack(back);

                    addCard(card);
                }
            }
        }
    }

    metadataFile.close();
    cardsFile.close();

    utils::removeFile(metadataPath);
    utils::removeFile(cardsPath);
    utils::copyDirectory(getDeckPath(), tempFolder);

    return true;
}

bool Deck::exportToTxt(QString fileName)
{
    const QChar sep('\t');
    QTextStream s;
    QFile file(fileName);

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if(!file.isOpen())
        return false;

    s.setDevice(&file);
    s.setCodec("UTF-8");

    Card *card = 0;
    int count = cards.count();
    for(int index=0;index<count;index++) {
        card = cards.at(index);

        s << card->getFrontPlain().simplified() << sep << card->getBackPlain().simplified();
    };

    return true;
}

bool Deck::importFromTxt(QString fileName)
{
    const QChar sep('\t');
    QTextStream s;
    QFile file(fileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!file.isOpen())
        return false;

    s.setDevice(&file);
    s.setCodec("UTF-8");

    QStringList sl;
    QString l = s.readLine();
    while (!s.atEnd()) {
        sl = l.split(sep);

        if(sl.size()>1) {
            Card *card = new Card();

            card->updateFront(sl[0]);
            card->updateBack(sl[1]);

            addCard(card);
        }

        l = s.readLine();
    };
    
    return true;
}

bool Deck::importDana(QString fileName)
{
    QFileInfo fi(fileName);
    QString baseName = fi.baseName().toLower();

    QString tempFolder = utils::combinePaths(tempPath(), baseName);
    QString deckPath = utils::combinePaths(tempFolder, "deck.xml"); 
    QString iconPath = utils::combinePaths(tempFolder, "icon.png"); 
    
    utils::createDirectory(tempFolder);
    
    if(!zlibWrappr::unzipFolder(fileName, tempFolder)) {
        return false;
    }

    /// 
    importFromXml(deckPath);

    utils::removeFile(deckPath);
    utils::copyDirectory(getDeckPath(), tempFolder);

    /// load icon pixmap
    loadPixmap( iconPath );

    return true;
}

bool Deck::importFromXml(QString fileName)
{
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;
    QFile file(fileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!file.isOpen())
        return false;

    if (!domDocument.setContent(&file, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qDebug() << QString("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr);
        return false;
    }

    QDomElement root = domDocument.documentElement();
    if (root.tagName().toLower() != XML_TAG_ROOT) {
        qDebug() << "root node is mismatched.";

        return false;
    }

    QDomElement nodeDeck;
    QDomElement nodeCards;
    QDomElement elnode;

    nodeDeck = root.firstChildElement(XML_TAG_DECK);
    if(nodeDeck.isNull()) {
        qDebug() << "deck node is mismatched.";

        return false;
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_NAME);
    if(!elnode.isNull()) {
        name=elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_DESC);
    if(!elnode.isNull()) {
        desc=elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_ICON);
    if(!elnode.isNull()) {
        
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_GUID);
    if(!elnode.isNull()) {
        guid=QUuid(elnode.text());
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_CREATED);
    if(!elnode.isNull()) {
        createdTime=QDateTime::fromString(elnode.text());
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_UPDATED);
    if(!elnode.isNull()) {
        updatedTime=QDateTime::fromString(elnode.text());
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_AUTHOR);
    if(!elnode.isNull()) {
        author=elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_TAGS);
    if(!elnode.isNull()) {
        tags=elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_FLAGS);
    if(!elnode.isNull()) {
        flags=elnode.text().toUInt();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_INHAND);
    if(!elnode.isNull()) {
        inhand=elnode.text().toInt();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_FORMAT);
    if(!elnode.isNull()) {
        //// Converting QDomElement to QString
        //// http://qt-project.org/doc/qt-5/qdomnode.html#save
        QString str;
        QTextStream stream(&str);
        elnode.save(stream, 4);
        format.fromString(str);
    }

    nodeCards = nodeDeck.firstChildElement(XML_TAG_CARDS);
    if(!elnode.isNull()) {
        QDomNodeList nodes = root.elementsByTagName(XML_TAG_CARD);
        QDomNode nodeCard;
        QString front, back;
        int flags = 0;

        int count = nodes.count();
        for(int no = 0; no < count; no++) {
            nodeCard = nodes.at(no);
            flags = 0;
            front.clear();
            back.clear();

            elnode = nodeCard.firstChildElement(XML_TAG_FRONT);
            if(!elnode.isNull()) {
                front = elnode.text();
            }

            elnode = nodeCard.firstChildElement(XML_TAG_BACK);            
            if(!elnode.isNull()) {
                back = elnode.text();
            }

            elnode = nodeCard.firstChildElement(XML_TAG_FLAGS);            
            if(!elnode.isNull()) {
                flags = elnode.text().toInt();
            }

            if(!front.isEmpty()) {
                Card *card = new Card;

                card->updateFront(front);
                card->updateBack(back);
                card->setFlags(flags);

                addCard(card);
            }
        }
    }
        
    file.close();

    return true;
}

bool Deck::exportToDana(QString fileName)
{
    QFileInfo fi(fileName);
    QString baseName = fi.baseName().toLower();
    
    QString tempFolder = utils::combinePaths(tempPath(), baseName);
    QString deckFile = utils::combinePaths(tempFolder, "deck.xml"); 
        
    utils::removeDirectory(tempFolder);
    utils::createDirectory(tempFolder);
    
    if(!exportToXml(deckFile))
        return false;

    utils::copyDirectory(tempFolder, getDeckPath());

    if(!zlibWrappr::zipFolder(tempFolder, fileName)) {
        return false;
    }

    return true;  
}

bool Deck::exportToXml(QString fileName)
{
    QXmlStreamWriter xml;
    QFile file(fileName);

    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if(!file.isOpen())
        return false;

    xml.setAutoFormatting(true);
    xml.setCodec("UTF-8");

    xml.setDevice(&file);

    xml.writeStartDocument();

    /// --<dana>
    xml.writeStartElement(XML_TAG_ROOT);

    xml.writeStartElement(XML_TAG_VERSION);
    xml.writeCharacters(appVersionString());
    xml.writeEndElement();

    /// --<deck>
    xml.writeStartElement(XML_TAG_DECK);

    xml.writeStartElement(XML_TAG_NAME);
    xml.writeCharacters(name);
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_DESC);
    xml.writeCharacters(desc);
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_ICON);
    xml.writeCharacters("icon.png");
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_GUID);
    xml.writeCharacters(guid.toString());
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_CREATED);
    xml.writeCharacters(createdTime.toString());
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_UPDATED);
    xml.writeCharacters(updatedTime.toString());
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_AUTHOR);
    xml.writeCharacters(author);
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_TAGS);
    xml.writeCharacters(tags);
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_FLAGS);
    xml.writeCharacters(QString::number(flags));
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_INHAND);
    xml.writeCharacters(QString::number(inhand));
    xml.writeEndElement();

    xml.writeDTD(format.toString());

    xml.writeEndElement();
    /// --</deck>

    /// --<cards>
    xml.writeStartElement(XML_TAG_CARDS);

    Card *card = 0;
    int count = cards.count();
    for(int index = 0; index < count; index++) {
        card = cards.at(index);

        xml.writeStartElement(XML_TAG_CARD);
        // ---------------------------------
        xml.writeStartElement(XML_TAG_FRONT);
        xml.writeCDATA(card->getFront());
        xml.writeEndElement();

        xml.writeStartElement(XML_TAG_BACK);
        xml.writeCDATA(card->getBack());
        xml.writeEndElement();

        xml.writeStartElement(XML_TAG_FLAGS);
        xml.writeCDATA(QString::number(card->getFlags()));
        xml.writeEndElement();

        /*
        xml.writeStartElement("level");
        xml.writeDTD(QString::number(card->getLevel()));
        xml.writeEndElement();
        */
        // ---------------------------------
        xml.writeEndElement();
    }
    xml.writeEndElement();
    /// --</cards>

    xml.writeEndDocument();
    /// --</dana>

    file.close();

    return true;
}

void Deck::loadPixmap(QString path)
{
    pixmap.load(path);
}
