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

#include "deckformat.h"
#include "constants.h"

#include <QXmlStreamWriter>
#include <QDomElement>
#include <QtDebug>

DeckFormat::DeckFormat(QObject *parent)
    : QObject(parent)
{
    frontEditorPolicy = AcceptRich;
    backEditorPolicy = AcceptRich;
}

DeckFormat::DeckFormat(const DeckFormat &rhs)
{
    *this=rhs;
}

DeckFormat &DeckFormat::operator=  (const DeckFormat &rhs)
{
    frontCharFormat   = rhs.frontCharFormat  ;
    backCharFormat    = rhs.backCharFormat   ;
    frontBlockFormat  = rhs.frontBlockFormat ;
    backBlockFormat   = rhs.backBlockFormat  ;
    frontEditorPolicy = rhs.frontEditorPolicy;
    backEditorPolicy  = rhs.backEditorPolicy ;

    return *this;
}

QString DeckFormat::toString()
{
    QString format;
    QXmlStreamWriter xml(&format);
    
    xml.setAutoFormatting(true);
    xml.setCodec("UTF-8");

   //// xml.setDevice(&file);

    xml.writeStartElement(XML_TAG_FORMAT);

    xml.writeStartElement(XML_TAG_FRONT);
    xml.writeStartElement(XML_TAG_FORMAT_FONT);
    xml.writeCharacters(frontCharFormat.font().toString());
    xml.writeEndElement();
    xml.writeStartElement(XML_TAG_FORMAT_FOREGROUND);
    xml.writeCharacters(QString::number(frontCharFormat.foreground().color().rgb()));
    xml.writeEndElement();
    xml.writeStartElement(XML_TAG_FORMAT_ALIGNMENT);
    xml.writeCharacters(QString::number(frontBlockFormat.alignment()));
    xml.writeEndElement();
    xml.writeStartElement(XML_TAG_FORMAT_POLICY);
    xml.writeCharacters(QString::number(frontEditorPolicy));
    xml.writeEndElement();
    xml.writeEndElement();

    xml.writeStartElement(XML_TAG_BACK);
    xml.writeStartElement(XML_TAG_FORMAT_FONT);
    xml.writeCharacters(backCharFormat.font().toString());
    xml.writeEndElement();
    xml.writeStartElement(XML_TAG_FORMAT_FOREGROUND);
    xml.writeCharacters(QString::number(backCharFormat.foreground().color().rgb()));
    xml.writeEndElement();
    xml.writeStartElement(XML_TAG_FORMAT_ALIGNMENT);
    xml.writeCharacters(QString::number(backBlockFormat.alignment()));
    xml.writeEndElement();
    xml.writeStartElement(XML_TAG_FORMAT_POLICY);
    xml.writeCharacters(QString::number(backEditorPolicy));
    xml.writeEndElement();
    xml.writeEndElement();

    xml.writeEndElement();

    return format;
}

void DeckFormat::fromString(QString format)
{
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(format, true, &errorStr, &errorLine, &errorColumn)) {
        qCritical() << QString("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr);
        return;
    }


    QDomElement root =  domDocument.firstChildElement(XML_TAG_FORMAT);
    if(!root.isNull()) {

        QDomElement el =  root.firstChildElement(XML_TAG_FRONT);
        if(!el.isNull()) {

            QDomElement el2 = el.firstChildElement(XML_TAG_FORMAT_FONT);
            if(!el2.isNull()) {
                QFont f;
                f.fromString(el2.text());
                frontCharFormat.setFont(f);
            }

            el2 = el.firstChildElement(XML_TAG_FORMAT_FOREGROUND);
            if(!el2.isNull()) {
                QColor c(el2.text().toUInt());
                frontCharFormat.setForeground(c);
            }

            el2 = el.firstChildElement(XML_TAG_FORMAT_ALIGNMENT);
            if(!el2.isNull()) {
                frontBlockFormat.setAlignment((Qt::Alignment)el2.text().toInt());
            }

            el2 = el.firstChildElement(XML_TAG_FORMAT_POLICY);
            if(!el2.isNull()) {
                frontEditorPolicy = (EditorPolicy)el2.text().toInt();
            }
        }

        el = root.firstChildElement(XML_TAG_BACK);
        if(!el.isNull()) {
            QDomElement el2 = el.firstChildElement(XML_TAG_FORMAT_FONT);
            if(!el2.isNull()) {
                QFont f;
                f.fromString(el2.text());
                backCharFormat.setFont(f);
            }

            el2 = el.firstChildElement(XML_TAG_FORMAT_FOREGROUND);
            if(!el2.isNull()) {
                QColor c(QRgb(el2.text().toUInt()));
                backCharFormat.setForeground(c);
            }

            el2 = el.firstChildElement(XML_TAG_FORMAT_ALIGNMENT);
            if(!el2.isNull()) {
                backBlockFormat.setAlignment((Qt::Alignment)el2.text().toInt());
            }

            el2 = el.firstChildElement(XML_TAG_FORMAT_POLICY);
            if(!el2.isNull()) {
                backEditorPolicy = (EditorPolicy)el2.text().toInt();
            }
        }
    }
}