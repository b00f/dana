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

#ifndef __DECKFORMAT_H
#define __DECKFORMAT_H

#include <QObject>
#include <QTextCharFormat>


class DeckFormat 
    : public QObject
{
    Q_OBJECT

public:
    enum EditorPolicy {
        AcceptRich   = 0,
        AcceptPlain     ,
    };

    DeckFormat(QObject *parent = 0);
    DeckFormat(const DeckFormat &rhs, QObject *parent = 0);

    DeckFormat &operator=  (const DeckFormat &rhs);
    
    QString toString();
    void fromString(QString format);

    QTextCharFormat  frontCharFormat  ;
    QTextCharFormat  backCharFormat   ;
    QTextBlockFormat frontBlockFormat ;
    QTextBlockFormat backBlockFormat  ;
    EditorPolicy     frontEditorPolicy;
    EditorPolicy     backEditorPolicy ;

};

#endif // __DECKFORMAT_H
