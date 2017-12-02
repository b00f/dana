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

#include "ideck.h"
#include "constants.h"

iDeck::iDeck(QObject *parent)
    : Deck(Type_iDeck, parent)
{
}

void iDeck::saveDeck()
{
}

void iDeck::removeDeck()
{

}

bool iDeck::openDeck(QVariant param)
{
    Q_UNUSED(param);
    return false;
}

bool iDeck::openDeck(const QDomNode &nodeDeck)
{
    QDomElement elnode;

    elnode = nodeDeck.firstChildElement(XML_TAG_ID);
    if(!elnode.isNull()) {
        id = elnode.text().toInt();
    }
    elnode = nodeDeck.firstChildElement(XML_TAG_NAME);
    if(!elnode.isNull()) {
        name = elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_DESC);
    if(!elnode.isNull()) {
        desc = elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_ICON);
    if(!elnode.isNull()) {
        loadPixmap( elnode.text() );
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_GUID);
    if(!elnode.isNull()) {
        guid = QUuid(elnode.text());
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_CREATED);
    if(!elnode.isNull()) {
        createdTime = QDateTime::fromString(elnode.text(), "yyyy-MM-dd hh:mm:ss");
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_UPDATED);
    if(!elnode.isNull()) {
        updatedTime = QDateTime::fromString(elnode.text(), "yyyy-MM-dd hh:mm:ss");
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_AUTHOR);
    if(!elnode.isNull()) {
        author = elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_TAGS);
    if(!elnode.isNull()) {
        tags = elnode.text();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_FLAGS);
    if(!elnode.isNull()) {
        flags = elnode.text().toUInt();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_RATING);
    if(!elnode.isNull()) {
        rating = elnode.text().toInt();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_INHAND);
    if(!elnode.isNull()) {
        inhand =  elnode.text().toInt();
    }

    elnode = nodeDeck.firstChildElement(XML_TAG_DOWNLOADS);
    if(!elnode.isNull()) {
        downloads = elnode.text().toInt();
    }

    return true;
}

void iDeck::closeDeck(QVariant param)
{
    Q_UNUSED(param)
}

void iDeck::setRating(int _rating)
{
    rating = _rating;
}

QString iDeck::getDeckPath() const
{
    return QString();
}


int iDeck::getRating()
{
    return rating;
}

int iDeck::getDownloads()
{
    return downloads;
}

void iDeck::loadPixmap(QString path)
{
    QUrl imageUrl(path);

    downloader = new FileDownloader(path, this);

    connect(downloader, SIGNAL(downloaded()), SLOT(loadImage()));
}

void iDeck::loadImage()
{
    pixmap.loadFromData(downloader->downloadedData());
}
